#include "stringObject.h"
#include "dictObject.h"

PyDictObject* g_internDict = NULL;

PyObject* PyString_Create(char* value, int length)
{
	//create object
	PyStringObject* object = new PyStringObject;
	object->hashValue = -1;
	object->refCount = 1;
	object->type = &PyString_Type;

	//set value
	memcpy(object->value, value, length);
	object->value[length] = '\0';
	object->length = length;
	return (PyObject*)object;
}

void PyString_InternInPlace(PyObject** object)
{
	PyStringObject* strObject = (PyStringObject*)(*object);
	if(g_internDict == NULL)
	{
		g_internDict = (PyDictObject*)PyDict_Create();
	}

	PyObject* result = PyDict_GetItem((PyObject*)g_internDict, (PyObject*)strObject);
	if(result != NULL)
	{
		//		cout << "Already interned!!!" << endl;
		*object = result;
		return;
	}

	//	cout << "Intern it!!!" << endl;
	PyDict_SetItem((PyObject*)g_internDict, (PyObject*)strObject, (PyObject*)strObject);
}

const char* PyString_GetRawString(PyObject* object)
{
	if(!CheckType("PyString_GetRawString", object, &PyString_Type))
	{
		return NULL;
	}

	PyStringObject* strObject = (PyStringObject*)object;
	return strObject->value;
}

int PyString_GetLength(PyObject* object)
{
	if(!CheckType("PyString_GetLength", object, &PyString_Type))
	{
		return NULL;
	}

	PyStringObject* strObject = (PyStringObject*)object;
	return strObject->length;
}

/************************************************************************/
//function for PyString_Type
static void string_print(PyObject* object, FILE* target=stdout)
{
	if(!CheckType("string_print", object, &PyString_Type))
	{
		return;
	}
	PyStringObject* strObject = (PyStringObject*)object;
	fprintf(target, "%s", strObject->value);
}

static long string_hash(PyObject* object)
{
	if(!CheckType("string_hash", object, &PyString_Type))
	{
		return -1;
	}

	PyStringObject* strObject = (PyStringObject*)object;
	register int len;
	register unsigned char *p;
	register long x;

	if (strObject->hashValue != -1)
		return strObject->hashValue;
	len = strObject->length;
	p = (unsigned char *)strObject->value;
	x = *p << 7;
	while (--len >= 0)
		x = (1000003*x) ^ *p++;
	x ^= strObject->length;
	if (x == -1)
		x = -2;
	strObject->hashValue = x;
	return x;
}

PyTypeObject PyString_Type = 
{
	PyObject_HEAD_INIT(&PyType_Type),
		"string",
		string_print,
		0,
		string_hash
};

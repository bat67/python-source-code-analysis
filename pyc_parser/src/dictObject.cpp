#include "dictObject.h"
#include "intObject.h"

PyObject* PyDict_Create()
{
	//create object
	PyDictObject* object = new PyDictObject;
	object->refCount = 1;
	object->type = &PyDict_Type;

	return (PyObject*)object;
}

PyObject* PyDict_GetItem(PyObject* target, PyObject* key)
{
	if(!CheckType("PyDict_GetItem", target, &PyDict_Type))
	{
		return NULL;
	}

	long keyHashValue = (key->type)->hash(key);
	map<PyObject*, PyObject*>& dict = ((PyDictObject*)target)->dict;
	map<PyObject*, PyObject*>::iterator it = dict.begin();
	map<PyObject*, PyObject*>::iterator end = dict.end();
	for( ; it != end; ++it)
	{
		PyObject* tempKey = it->first;
		long tempKeyHashValue = (tempKey->type)->hash(tempKey);
		if(keyHashValue == tempKeyHashValue)
		{
			return it->second;
		}
	}
	return NULL;
}

int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value)
{
	if(!CheckType("PyDict_SetItem", target, &PyDict_Type))
	{
		return -1;
	}

	long keyHashValue = (key->type)->hash(key);
	PyObject* intKey = PyInt_Create(keyHashValue);

	PyDictObject* dictObject = (PyDictObject*)target;
	(dictObject->dict).insert(map<PyObject*, PyObject*>::value_type(intKey, value));
	//	cout << "Now the size of dict is : " << dictObject->dict.size() << endl;
	return 0;
}

/***********************************************************************/
//function for PyDict_Type
static void dict_print(PyObject* object, FILE* target=stdout)
{
	if(!CheckType("dict_print", object, &PyDict_Type))
		return;

	PyDictObject* dictObject = (PyDictObject*)object;
	cout << "{";
	map<PyObject*, PyObject*>::iterator it = (dictObject->dict).begin();
	map<PyObject*, PyObject*>::iterator end = (dictObject->dict).end();
	for( ; it != end; ++it)
	{
		PyObject* key = it->first;
		PyObject* value = it->second;
		(key->type)->print(key, target);
		cout << ":";
		(value->type)->print(value, target);
		cout << ", ";
	}
	cout << "}" << endl;
}

PyTypeObject PyDict_Type = 
{
	PyObject_HEAD_INIT(&PyType_Type),
		"dict",
		dict_print,
		0
};

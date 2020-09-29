#include "strObject.h"
#include <stdio.h>
#include <string.h>

PyObject* CreatePyStrObject(const char* value)
{
	PyStrObject* object = new PyStrObject;
	object->refCount = 1;
	object->type = &PyStr_Type;
	memset(object->value, 0, 50);
	if(value != NULL)
	{
		strcpy(object->value, value);
	}
	return (PyObject*)object;
}

static void string_print(PyObject* object)
{
	PyStrObject* strObject = (PyStrObject*)object;
	printf("%s\n", strObject->value);
}

static PyObject* string_add(PyObject* left, PyObject* right)
{
	PyStrObject* leftStr = (PyStrObject*)left;
	PyStrObject* rightStr = (PyStrObject*)right;
	PyStrObject* result = (PyStrObject*)CreatePyStrObject(NULL);
	if(result == NULL)
	{
		printf("We have not enough memory!!");
	}
	else
	{
		strcpy(result->value, leftStr->value);
		strcat(result->value, rightStr->value);
	}
	return (PyObject*)result;
}

PyTypeObject PyStr_Type = 
{
	PyObject_HEAD_INIT(&PyType_Type),
		"str",
		string_print,
		string_add
};

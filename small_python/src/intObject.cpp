#include "intObject.h"
#include <stdio.h>

PyObject* CreatePyIntObject(int value)
{
	PyIntObject* object = new PyIntObject;
	object->refCount = 1;
	object->type = &PyInt_Type;
	object->value = value;
	return (PyObject*)object;
}

static void int_print(PyObject* object)
{
	PyIntObject* intObject = (PyIntObject*)object;
	printf("%d\n", intObject->value);
}

static PyObject* int_add(PyObject* left, PyObject* right)
{
	PyIntObject* leftInt = (PyIntObject*)left;
	PyIntObject* rightInt = (PyIntObject*)right;
	PyIntObject* result = (PyIntObject*)CreatePyIntObject(0);
	if(result == NULL)
	{
		printf("We have not enough memory!!");
	}
	else
	{
		result->value = leftInt->value + rightInt->value;
	}
	return (PyObject*)result;
}

PyTypeObject PyInt_Type = 
{
	PyObject_HEAD_INIT(&PyType_Type),
	"int",
	int_print,
	int_add
};

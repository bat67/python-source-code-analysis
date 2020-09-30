#include "intObject.h"

PyObject* PyInt_Create(int value)
{
	PyIntObject* object = new PyIntObject;
	object->refCount = 1;
	object->type = &PyInt_Type;
	object->value = value;
	return (PyObject*)object;
}

long PyInt_GetRawValue(PyObject* object)
{
	if(!CheckType("PyInt_GetRawValue", object, &PyInt_Type))
	{
		return 0;
	}

	PyIntObject* intObject = (PyIntObject*)object;
	return intObject->value;
}

/*************************************************************************/
//functions for PyInt_Type
static void int_print(PyObject* object, FILE* target=stdout)
{
	PyIntObject* intObject = (PyIntObject*)object;
	fprintf(target, "%d", intObject->value);
}

static long int_hash(PyObject* object)
{
	PyIntObject* intObject = (PyIntObject*)object;
	return intObject->value;
}

static PyObject* int_add(PyObject* left, PyObject* right)
{
	PyIntObject* leftInt = (PyIntObject*)left;
	PyIntObject* rightInt = (PyIntObject*)right;
	PyIntObject* result = (PyIntObject*)PyInt_Create(0);
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
		int_add,
		int_hash
};

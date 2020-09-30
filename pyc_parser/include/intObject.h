#ifndef __SPY_INTOBJECT_H_
#define __SPY_INTOBJECT_H_

#include "object.h"

typedef struct tagPyIntObject
{
	PyObject_HEAD;
	int value;
}PyIntObject;

extern PyTypeObject PyInt_Type;

PyObject* PyInt_Create(int value);
long PyInt_GetRawValue(PyObject* object);
#endif

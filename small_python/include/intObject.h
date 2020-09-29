#ifndef __PYTHONREADING_INTOBJECT_H_
#define __PYTHONREADING_INTOBJECT_H_

#include "object.h"

typedef struct tagPyIntObject
{
	PyObject_HEAD;
	int value;
}PyIntObject;

extern PyTypeObject PyInt_Type;

PyObject* CreatePyIntObject(int value);
#endif

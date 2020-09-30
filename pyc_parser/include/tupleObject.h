#ifndef __SPY_TUPLEOBJECT_H_
#define __SPY_TUPLEOBJECT_H_

#include "object.h"

typedef struct tagPyTupleObject
{
	PyObject_HEAD;
	int size;
	vector<PyObject*> tuple;
}PyTupleObject;

extern PyTypeObject PyTuple_Type;

PyObject* PyTuple_Create(int size);
void PyTuple_AddItem(PyObject* object, PyObject* item);
int PyTuple_GetSize(PyObject* object);
PyObject* PyTuple_GetItem(PyObject* object, int index);
#endif

#ifndef __SPY_DICTOBJECT_H_
#define __SPY_DICTOBJECT_H_

#include "object.h"

typedef struct tagPyDictObject
{
	PyObject_HEAD;
	map<PyObject*, PyObject*> dict;
}PyDictObject;

extern PyTypeObject PyDict_Type;

PyObject* PyDict_Create();
int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value);
PyObject* PyDict_GetItem(PyObject* target, PyObject* key);
#endif

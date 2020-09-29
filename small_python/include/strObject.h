#ifndef __PYTHONREADING_STROBJECT_H_
#define __PYTHONREADING_STROBJECT_H_

#include "object.h"

typedef struct tagPyStrObject
{
	PyObject_HEAD;
	char value[50];
}PyStrObject;

extern PyTypeObject PyStr_Type;

PyObject* CreatePyStrObject(const char* value);
#endif

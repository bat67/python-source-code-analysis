#ifndef __SPY_STRINGOBJECT_H_
#define __SPY_STRINGOBJECT_H_

#include "object.h"

typedef struct tagPyStringObject
{
	PyObject_HEAD;
	long hashValue;
	char value[1024];
	int length;
}PyStringObject;

extern PyTypeObject PyString_Type;

PyObject* PyString_Create(char* value, int length);
void PyString_InternInPlace(PyObject** object);
const char* PyString_GetRawString(PyObject* object);
int PyString_GetLength(PyObject* object);
#endif

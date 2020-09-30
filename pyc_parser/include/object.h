#ifndef __SPY_OBJECT_H_
#define __SPY_OBJECT_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

//definition of PyObject
#define PyObject_HEAD \
	int refCount;\
struct tagPyTypeObject *type

#define PyObject_HEAD_INIT(typePtr)\
	0, typePtr

typedef struct tagPyObject
{
	PyObject_HEAD;
}PyObject;

//definition of PyTypeObject
typedef void (*PrintFun)(PyObject* object, FILE* target);
typedef PyObject* (*AddFun)(PyObject* left, PyObject* right);
typedef long (*HashFun)(PyObject* object);

typedef struct tagPyTypeObject
{
	PyObject_HEAD;
	char* name;
	PrintFun print;
	AddFun add;
	HashFun hash;
}PyTypeObject;

extern PyTypeObject PyType_Type;
extern PyObject PyNoneObject;
#define PyNone (&PyNoneObject);

bool CheckType(const char* caller, PyObject* object, PyTypeObject* type);

#endif

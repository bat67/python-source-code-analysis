#ifndef __PYTHONREADING_OBJECT_H_
#define __PYTHONREADING_OBJECT_H_

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
typedef void (*PrintFun)(PyObject* object);
typedef PyObject* (*AddFun)(PyObject* left, PyObject* right);

typedef struct tagPyTypeObject
{
	PyObject_HEAD;
	char* name;
	PrintFun print;
	AddFun add;
}PyTypeObject;

extern PyTypeObject PyType_Type;

#endif

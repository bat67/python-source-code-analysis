#ifndef __SPY_CODEOBJECT_H_
#define __SPY_CODEOBJECT_H_

#include "object.h"

typedef struct tagPyCodeObject
{
	PyObject_HEAD;
	int argCount;	/* #arguments, except *args */
	int localCount;		/* #local variables */
	int stackSize;	/* #entries needed for evaluation stack */
	int flags;		/* CO_..., see below */
	PyObject* code;		/* instruction opcodes */
	PyObject* consts;	/* list (constants used) */
	PyObject* names;		/* list of strings (names used) */
	PyObject* varNames;	/* tuple of strings (local variable names) */
	PyObject* freeVars;	/* tuple of strings (free variable names) */
	PyObject* cellVars;      /* tuple of strings (cell variable names) */
	/* The rest doesn't count for hash/cmp */
	PyObject* fileName;	/* string (where it was loaded from) */
	PyObject* name;		/* string (name, for reference) */
	int firstLineNo;		/* first source line number */
	PyObject* lnotab;	/* string (encoding addr<->lineno mapping) */
}PyCodeObject;

extern PyTypeObject PyCode_Type;

PyObject* PyCode_Create(int, int, int, int, PyObject*, PyObject*, PyObject*, PyObject*, PyObject*, PyObject*, PyObject*, PyObject*, int, PyObject*);

#endif

#include "codeObject.h"
#include "stringObject.h"

PyObject* PyCode_Create(int argCount, int localCount, int stackSize, int flags,
						PyObject *code, PyObject *consts, PyObject *names,
						PyObject *varNames, PyObject *freeVars, PyObject *cellVars,
						PyObject *fileName, PyObject *name, int firstLineNo,
						PyObject *lnotab)
{
	PyCodeObject* object = new PyCodeObject;
	object->refCount = 1;
	object->type = &PyCode_Type;

	object->argCount = argCount;
	object->localCount = localCount;
	object->stackSize = stackSize;
	object->flags = flags;
	object->code = code;
	object->consts = consts;
	object->names = names;
	object->varNames = varNames;
	object->freeVars = freeVars;
	object->cellVars = cellVars;
	object->fileName = fileName;
	object->name = name;
	object->firstLineNo = firstLineNo;
	object->lnotab = lnotab;

	return (PyObject*)object;
}

/*************************************************************************/
//functions for PyCode_Type
static void code_print(PyObject* object, FILE* target=stdout)
{
	if(object->type != &PyCode_Type)
	{
		cout << "[Error]string_print : object is not a string object";
		return;
	}

	PyCodeObject* codeObject = (PyCodeObject*)object;
	cout << "<code, ";
	PyString_Type.print(codeObject->name, target);
	printf(" @%p>", codeObject);
}

PyTypeObject PyCode_Type = 
{
	PyObject_HEAD_INIT(&PyType_Type),
		"code",
		code_print,
		0
};

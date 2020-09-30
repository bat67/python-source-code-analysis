#include "object.h"

PyTypeObject PyType_Type = 
{
	PyObject_HEAD_INIT(&PyType_Type),
	"type",
	0,
	0
};

static void nonePrint(PyObject* object, FILE* target=stdout)
{
	fprintf(target, "none");
}

static PyTypeObject PyNone_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	"none",
	nonePrint,
	0
};

PyObject PyNoneObject = 
{
	PyObject_HEAD_INIT(&PyNone_Type)
};

//function
bool CheckType(const char* caller, PyObject* object, PyTypeObject* type)
{
	if(object->type != type)
	{
		cout << "[Error]" << caller  << " : object is not a " << type->name << " object" << endl;
		return false;
	}
	return true;
}

#include "tupleObject.h"

PyObject* PyTuple_Create(int size)
{
	//create object
	PyTupleObject* object = new PyTupleObject;
	object->refCount = 1;
	object->type = &PyTuple_Type;
	object->size = size;

	return (PyObject*)object;
}

void PyTuple_AddItem(PyObject* object, PyObject* item)
{
	if(!CheckType("PyTuple_AddItem", object, &PyTuple_Type))
		return;

	PyTupleObject* tupleObject = (PyTupleObject*)object;
	if((tupleObject->tuple).size() >= tupleObject->size)
	{
		cout << "[Error]PyTuple_AddItem : size over flow" << endl;
		return;
	}

	(tupleObject->tuple).push_back(item);
}

int PyTuple_GetSize(PyObject* object)
{
	if(!CheckType("PyTuple_GetSize", object, &PyTuple_Type))
	{
		return -1;
	}

	PyTupleObject* tupleObject = (PyTupleObject*)object;
	return (tupleObject->tuple).size();
}

PyObject* PyTuple_GetItem(PyObject* object, int index)
{
	if(!CheckType("PyTuple_GetItem", object, &PyTuple_Type))
	{
		return NULL;
	}

	PyTupleObject* tupleObject = (PyTupleObject*)object;
	return (tupleObject->tuple)[index];
}

/***********************************************************************/
//functions for PyTuple_Type
static void tuple_print(PyObject* object, FILE* target=stdout)
{
	if(object->type != &PyTuple_Type)
	{
		cout << "[Error]dict_print : object is not a dict object";
		return;
	}

	PyTupleObject* tupleObject = (PyTupleObject*)object;
	cout << "(";
	vector<PyObject*>::iterator it = (tupleObject->tuple).begin();
	vector<PyObject*>::iterator end = (tupleObject->tuple).end();
	for( ; it != end; ++it)
	{
		PyObject* item = *it;
		(item->type)->print(item, target);
		cout << ", ";
	}
	cout << ")" << endl;
}

PyTypeObject PyTuple_Type = 
{
	PyObject_HEAD_INIT(&PyType_Type),
		"tuple",
		tuple_print,
		0
};

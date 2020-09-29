#ifndef __PYTHONREADING_ENGINE_H_
#define __PYTHONREADING_ENGINE_H_

#include "object.h"
#include "intObject.h"
#include "strObject.h"

#include <iostream>
#include <string>
#include <map>

char* info = "********** Python Research **********\nInput 'exit' to exit\n";
char* prompt = ">>> ";

class ExcuteEngine
{
public:
	void Excute()
	{
		cout << info;
		cout << prompt;
		while(getline(cin, m_Command))
		{
			if(m_Command.size() == 0)
			{
				cout << prompt;
				continue;
			}
			else if(m_Command == "exit")
			{
				return;
			}
			else
			{
				ExcuteCommand(m_Command);
			}
			cout << prompt;
		}
	}

private:
	void ExcuteCommand(string& command)
	{
		string::size_type pos = 0;
		if((pos = command.find("print ")) != string::npos)
		{
			ExcutePrint(command.substr(6));
		}
		else if((pos = command.find(" = ")) != string::npos)
		{
			string target = command.substr(0, pos);
			string source = command.substr(pos+3);
			ExcuteAdd(target, source);
		}
		else {
			cout << "[Error] : Can not recognize : " << command <<  endl;
		}
	}

	void ExcutePrint(string symbol)
	{
		PyObject* object = GetObjectFromSymbol(symbol);
		if(object != NULL)
		{
			PyTypeObject* type = object->type;
			type->print(object);
		}
	}

	void ExcuteAdd(string& target, string& source)
	{
		string::size_type pos;
		if(IsSourceAllDigit(source))
		{
			PyObject* intObject = CreatePyIntObject(atoi(source.c_str()));
			if(m_Symbol2Object.find(target) == m_Symbol2Object.end()) {
				m_Symbol2Object.insert(map<string, PyObject*>::value_type(target, intObject));
			}
			else {
				m_Symbol2Object[target] = intObject;
			}
		}
		else if(source.find("\"") != string::npos || source.find("'") != string::npos)
		{
			PyObject* strObject = CreatePyStrObject(source.substr(1, source.size()-2).c_str());
			if(m_Symbol2Object.find(target) == m_Symbol2Object.end()) {
				m_Symbol2Object.insert(map<string, PyObject*>::value_type(target, strObject));
			}
			else {
				m_Symbol2Object[target] = strObject;
			}
		}
		else if((pos = source.find("+")) != string::npos)
		{
			PyObject* leftObject = GetObjectFromSymbol(Trim(source.substr(0, pos)));
			PyObject* rightObject = GetObjectFromSymbol(Trim(source.substr(pos+1)));
			if(leftObject != NULL && right != NULL && leftObject->type == rightObject->type)
			{
				PyObject* result = (leftObject->type)->add(leftObject, rightObject);
				m_Symbol2Object.insert(map<string, PyObject*>::value_type(target, result));
			}
		}
	}

	bool IsSourceAllDigit(string& source)
	{
		string::size_type len = source.size();
		for(string::size_type i = 0; i < len; ++i)
		{
			if(!isdigit(source[i]))
			{
				return false;
			}
		}
		return true;
	}

	PyObject* GetObjectFromSymbol(string symbol)
	{
		map<string, PyObject*>::iterator it = m_Symbol2Object.find(symbol);
		if(it == m_Symbol2Object.end())
		{
			cout << "[Error] : " << symbol << " is not defined!!" << endl;
			return NULL;
		}
		return it->second;
	}

	string Trim(string symbol) {
		int length = symbol.length();

		int start = 0;
		while(symbol[start] == ' ') {
			++start;
		}

		int end = length-1;
		while(symbol[end] == ' ') {
			--end;
		}
		return symbol.substr(start, end+1);
	}
private:
	string m_Command;
	map<string, PyObject*> m_Symbol2Object;
};
#endif

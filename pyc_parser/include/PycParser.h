#ifndef __SPY_PYCPARSER_H_
#define __SPY_PYCPARSER_H_

#include <map>
#include <set>
#include <ctime>
using namespace std;

#include "reader.h"
#include "writer.h"
#include "codeObject.h"
#include "stringObject.h"
#include "intObject.h"
#include "tupleObject.h"
#include "opCode.h"

#define TYPE_UNKNOWN	'?'
#define TYPE_NULL	'0'
#define TYPE_NONE	'N'
#define TYPE_FALSE	'F'
#define TYPE_TRUE	'T'
#define TYPE_STOPITER	'S'
#define TYPE_ELLIPSIS   '.'
#define TYPE_INT	'i'
#define TYPE_INT64	'I'
#define TYPE_FLOAT	'f'
#define TYPE_BINARY_FLOAT	'g'
#define TYPE_COMPLEX		'x'
#define TYPE_BINARY_COMPLEX	'y'
#define TYPE_LONG	'l'
#define TYPE_STRING	's'
#define TYPE_INTERNED	't'
#define TYPE_STRINGREF	'R'
#define TYPE_TUPLE	'('
#define TYPE_LIST	'['
#define TYPE_DICT	'{'
#define TYPE_CODE	'c'
#define TYPE_UNICODE	'u'
#define TYPE_SET		'<'
#define TYPE_FROZENSET  	'>'

#define MAGIC (62131 | ((long)'\r'<<16) | ((long)'\n'<<24))

class PycParser
{
public:
	PyObject* Parse(const char* fileName)
	{
		m_StrIndexInList = 0;
		//open pyc file
		m_File = fopen(fileName, "rb");
		if(m_File == NULL)
		{
			cout << "[Error] : Can't open file " << fileName << endl;
			return NULL;
		}

		//open xml file writer
		m_Writer.open(fileName);

		if(ReadMagicNumber() == MAGIC)
		{
			cout << "[Info] : Valid Pyc File!" << endl;
		}
		else
		{
			cout << "[Info] : Invalid Pyc File!" << endl;
			return NULL;
		}

		long modifiedTime = ReadModifiedTime();
		cout << "[Info] : Last Modified Time : " << asctime(localtime(&modifiedTime)) << "\n\n\n";
		PyObject* code = ReadObject();

		//close the pyc file
		fclose(m_File);
		return code;
	}

private:
	int ReadMagicNumber()
	{
		return m_Reader.ReadInt(m_File);
	}

	int ReadModifiedTime()
	{
		return m_Reader.ReadInt(m_File);
	}

	PyObject* ReadObject()
	{
		int type = m_Reader.ReadByte(m_File);
		switch(type)
		{
		case TYPE_UNKNOWN:
			break;
		case TYPE_NULL:
			break;
		case TYPE_NONE:
			{
				m_Writer.Write("<NoneObject/>");
				return PyNone;
			}
			break;
		case TYPE_FALSE:
			cout << "False" << endl;
			break;
		case TYPE_TRUE:
			cout << "True" << endl;
			break;
		case TYPE_STOPITER:
			cout << "StopIter" << endl;
			break;
		case TYPE_ELLIPSIS:
			cout << "Ellipsis" << endl;
			break;
		case TYPE_INT:
			{
				int value = m_Reader.ReadInt(m_File);
				PyObject* object = PyInt_Create(value);
				sprintf(temp, "<int value=\"%d\"/>\0", value);
				m_Writer.Write(temp);
				return object;
			}
			break;
		case TYPE_INT64:
			cout << "Int64" << endl;
			break;
		case TYPE_FLOAT:
			cout << "Float" << endl;
			break;
		case TYPE_COMPLEX:
			cout << "Complex" << endl;
			break;
		case TYPE_LONG:
			cout << "Long" << endl;
			break;
		case TYPE_INTERNED:/*fall through*/
		case TYPE_STRING:
			{
				long length = m_Reader.ReadInt(m_File);
				char buffer[1024];
				buffer[length] = '\0';
				m_Reader.ReadString(buffer, length, m_File);
				PyObject* strObject = PyString_Create(buffer, length);
				//we replace the <> by [] to let the XML cna be displayed in browser
				if(buffer[0] == '<')
				{
					buffer[0] = '[';
				}
				if(buffer[length-1] == '>')
				{
					buffer[length-1] = ']';
				}
				if(type == TYPE_INTERNED)
				{
					PyString_InternInPlace(&strObject);
					m_vecInternedString.push_back(strObject);
					if(strlen(buffer) == length && IsTxtAsciiChar(buffer[0]))
					{
						cout << "string in buffer : " << buffer << endl;
						sprintf(temp, "<internStr index=\"%d\" length=\"%d\" value=\"%s\"/>\0", m_StrIndexInList++, length, buffer);
					}
					else
					{
						sprintf(temp, "<internStr index=\"%d\" length=\"%d\" value=\"binary\"/>\0", m_StrIndexInList++, length);
					}
				}
				else
				{			
					if(strlen(buffer) == length && IsTxtAsciiChar(buffer[0]))
					{
						cout << "string in buffer : " << buffer << endl;
						sprintf(temp, "<str length=\"%d\" value=\"%s\"/>\0", length, buffer);
					}
					else
					{
						sprintf(temp, "<str length=\"%d\" value=\"binary\"/>\0", length);
					}
				}
				m_Writer.Write(temp);
				return strObject;
			}
			break;
		case TYPE_STRINGREF:
			{
				int index = m_Reader.ReadInt(m_File);
				PyObject* strObject = m_vecInternedString[index];
				sprintf(temp, "<strRef index=\"%d\" value=\"%s\"/>\0", index, PyString_GetRawString(strObject));
				m_Writer.Write(temp);			
				return strObject;
			}
			break;
		case TYPE_TUPLE:
			{
				cout << "Tuple" << endl;
				int length = m_Reader.ReadInt(m_File);
				PyObject* tuple = PyTuple_Create(length);
				for(int i = 0; i < length; ++i)
				{
					PyObject* object = ReadObject();
					PyTuple_AddItem(tuple, object);
				}
				(tuple->type)->print(tuple, stdout);
				return tuple;
			}
			break;
		case TYPE_LIST:
			cout << "List" << endl;
			break;
		case TYPE_DICT:
			cout << "Dict" << endl;
			break;
		case TYPE_CODE:
			{
				//			cout << "==================== Begin Code ====================" << endl;
				m_Writer.Write("<codeObject>");
				int argCount = m_Reader.ReadInt(m_File);
				sprintf(temp, "<argCount value=\"%d\"/>\0", argCount);
				m_Writer.Write(temp);

				int localCount = m_Reader.ReadInt(m_File);
				sprintf(temp, "<localCount value=\"%d\"/>\0", localCount);
				m_Writer.Write(temp);

				int stackSize = m_Reader.ReadInt(m_File);
				sprintf(temp, "<stackSize value=\"%d\"/>\0", stackSize);
				m_Writer.Write(temp);

				int flags = m_Reader.ReadInt(m_File);
				sprintf(temp, "<flags value=\"%d\"/>\0", flags);
				m_Writer.Write(temp);
				//			cout << "***** Code *****" << endl;
				m_Writer.Write("<code>");
				PyObject* code = ReadObject();
				m_Writer.Write("</code>");
				//			cout << "***** Consts *****" << endl;
				m_Writer.Write("<consts>");
				PyObject* consts = ReadObject();
				m_Writer.Write("</consts>");
				//			cout << "***** Names *****" << endl;
				m_Writer.Write("<names>");
				PyObject* names = ReadObject();
				m_Writer.Write("</names>");
				//cout << "***** varNames *****" << endl;
				m_Writer.Write("<varNames>");
				PyObject* varNames = ReadObject();
				m_Writer.Write("</varNames>");
				//			cout << "***** freeVars *****" << endl;
				m_Writer.Write("<freeVars>");
				PyObject* freeVars = ReadObject();
				m_Writer.Write("</freeVars>");
				//			cout << "***** cellVars *****" << endl;
				m_Writer.Write("<cellVars>");
				PyObject* cellVars = ReadObject();
				m_Writer.Write("</cellVars>");
				//			cout << "***** fileName *****" << endl;
				m_Writer.Write("<fileName>");
				PyObject* fileName = ReadObject();
				m_Writer.Write("</fileName>");
				//			cout << "***** name *****" << endl;
				m_Writer.Write("<name>");
				PyObject* name = ReadObject();
				m_Writer.Write("</name>");
				//			cout << "***** firstLineNo *****" << endl;
				m_Writer.Write("<firstLineNo>");
				int firstLineNo = m_Reader.ReadInt(m_File);
				m_Writer.Write("</firstLineNo>");
				//			cout << "***** lnotab *****" << endl;
				m_Writer.Write("<lnotab>");
				PyObject* lnotab = ReadObject();
				ParseOpCode(code, lnotab, firstLineNo);
				m_Writer.Write("</lnotab>");
				m_Writer.Write("</codeObject>");
				//			cout << "==================== End Code ====================\n\n\n" << endl;

				PyObject* codeObject = PyCode_Create(
					argCount, localCount, stackSize, flags,
					code, consts, names, varNames,
					freeVars, cellVars, fileName, name,
					firstLineNo, lnotab
					);
				return codeObject;
			}
			break;
		case TYPE_UNICODE:
			cout << "Unicode" << endl;
			break;
		default:
			cout << "Can't reach this point" << endl;
			break;
		}
		return NULL;
	}

	void ParseOpCode(PyObject* code, PyObject* lnotab, int firstLine)
	{
		if(code->type != &PyString_Type)
		{
			cout << "[Error]ParseOpCode : code is not a PyStringObject" << endl;
			exit(1);
		}

		if(lnotab->type != &PyString_Type)
		{
			cout << "[Error]ParseOpCode : lnotab is not a PyStringObject" << endl;
			exit(1);
		}

		unsigned char* firstInstruction = (unsigned char*)PyString_GetRawString(code);
		unsigned char* nextInstruction = firstInstruction;
		int codeLength = PyString_GetLength(code);

		int opCode = -1;
		int opArg = -1;

		unsigned char* nextSourceLine = (unsigned char*)PyString_GetRawString(lnotab);
		unsigned short currentOpNo = 0;
		unsigned short currentLineNo = firstLine;
		int lnotabLength = PyString_GetLength(lnotab)/2;
		int lnotabIndex = 0;

#define NEXT_OP() (*nextInstruction++)
#define NEXT_ARG() (nextInstruction += 2, (nextInstruction[-1]<<8) + nextInstruction[-2])

		while(nextInstruction-firstInstruction < codeLength)
		{
			//get source code line in .py
			unsigned short delta = nextInstruction-firstInstruction;
			nextSourceLine = (unsigned char*)PyString_GetRawString(lnotab);
			currentOpNo = 0;
			currentLineNo = firstLine;
			for(int i = 0; i < lnotabLength; ++i)
			{
				currentOpNo += *(nextSourceLine++);
				if(currentOpNo > delta)
				{
					break;
				}
				currentLineNo += *(nextSourceLine++);
			}

			//get op code and its arguments
			opCode = NEXT_OP();
			opArg = -9999;
			if(HAS_ARG(opCode))
			{
				opArg = NEXT_ARG();
			}

			const char* codeName = m_OpCodeSet.GetStringById(opCode);

			if(opArg != -9999)
			{
				sprintf(temp, "<op code=\"%d\" codeName=\"%s\" arg=\"%d\" line=\"%d\"/>\0", opCode, codeName, opArg, currentLineNo);
			}
			else
			{
				sprintf(temp, "<op code=\"%d\" codeName=\"%s\" arg=\"none\" line=\"%d\"/>\0", opCode, codeName, currentLineNo);
			}
			m_Writer.Write(temp);
		}

	}

	bool IsTxtAsciiChar(char character)
	{
		if( (character >= 33/* for ! */) && (character <= 126/* for ~ */) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	OpCodeSet m_OpCodeSet;
	Writer m_Writer;
	Reader m_Reader;
	FILE *m_File;
	char temp[1024];
	int m_StrIndexInList;
	vector<PyObject*> m_vecInternedString; /* dict on marshal, list on unmarshal */
};
#endif

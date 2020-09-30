#ifndef __SPY_WRITER_H_
#define __SPY_WRITER_H_

#include <fstream>
using namespace std;

class Writer
{
public:
	Writer()
	{
		
	}


	~Writer()
	{
		if(m_OutFile)
		{
			m_OutFile << "</PycFile>" << endl;
			m_OutFile.close();
		}
	}

public:
	template<typename T>
	void Write(T value, bool newLine = true)
	{
		m_OutFile << value;
		if(newLine)
		{
			m_OutFile << "\n";
		}
	}

	void open(const char* pycFileName) {
		string name = pycFileName;
		size_t length = name.length();
		name[length-3] = 'x';
		name[length-2] = 'm';
		name[length-1] = 'l';
		m_OutFile.open(name.c_str());
		m_OutFile << "<PycFile>" << endl;
	}

private:
	ofstream m_OutFile;
};
#endif

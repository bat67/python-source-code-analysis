#include "PycParser.h"

int main(int argc, char* argv[])
{
		PycParser parser;
		if(argc != 2)
		{
			cout << "usage : PycParser <pyc file>" << endl;
			return -1;
		}
		PyObject* code = parser.Parse(argv[1]);
		return 0;
}

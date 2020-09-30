#ifndef __SPY_READER_H_
#define __SPY_READER_H_

class Reader
{
public:
	int ReadInt(FILE* file)
	{
		unsigned char number[5];
		number[4] = '\0';
		number[0] = fgetc(file);
		number[1] = fgetc(file);
		number[2] = fgetc(file);
		number[3] = fgetc(file);
		return *(int*)(number);
	}

	int ReadByte(FILE* file)
	{
		return fgetc(file);
	}

	void ReadString(char* buffer, int length, FILE* file)
	{
		fread(buffer, sizeof(char), length, file);
	}
};

#endif

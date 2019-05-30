#ifndef __SCANER
#define __SCANER
#include "defs.h"

class Scaner
{
public:
	Scaner(string);
	~Scaner(void);
	void loadFromFile(string);
	int scaner(LEX);
	void paintError(char*,char*);
	void setUK(int i);
	void setStr(int i);
	void setStb(int i);
	int getUK();
	int getStr();
	int getStb();
private:
	TEXT text;
	int uk;
	int str;
	int stb;
};
#endif
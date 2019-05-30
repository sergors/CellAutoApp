#pragma once
#include "Scaner.h"
#include "Tree.h"

class Parser
{
private:
	Scaner *scan;
	LEX l1;
	Tree *Root;
	DATA_TYPE type;
	int FlInt;
	float data_float;
	char data_char;
	bool data_bool;

public:
	Parser(Scaner *s);

	void S();
	void OpisaniePeremenn();
	void Block();
	void Operator();
	void Prisvaivanie();
	void While();
	DATA_TYPE Viragenie();
	DATA_TYPE V1();
	DATA_TYPE V2();
	DATA_TYPE V3();
	DATA_TYPE V4();

	~Parser(void);
};


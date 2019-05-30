#pragma once
#include "Scaner.h"
using namespace std;
enum DATA_TYPE
{
	TYPE_EMPTY=1,
	TYPE_FLOAT,
	TYPE_CHAR,
	TYPE_BOOL,
	TYPE_STRUCT
};
union DATA
{
	float data_float;
	char data_char;
	bool data_bool;
};
struct Node
{
	LEX id;
	DATA_TYPE DataType;
	char* TYPE;
	DATA DataValue;
};

class Tree
{
	Node *n;
	Tree *Up, *Left, *Right;
public:
	Tree(Tree *l, Tree *r, Tree *u, Node *d);
	Tree();
	~Tree();

	static Tree *Cur;

	Tree* CreateEmpty();
	Tree* SemInclude(LEX a, DATA_TYPE t, Scaner *sc);
	Tree* SemInclude(LEX a, char* t, Scaner *sc);
	void setLeft(Node *Data);
	void setRight(Node *Data);
	void setCur(Tree *a);
	Tree* getCur();
	float getDataFloat();
	char getDataChar();
	bool getDataBool();
	void setDataFloat(LEX zn);
	void setDataFloat(float n);

	void setDataChar(LEX zn);
	void setDataChar(char n);

	void setDataBool(LEX zn);
	void setDataBool(bool n);

	char * getId();

	Tree* FindUp(Tree *From, LEX id);
	Tree* FindUpOneLevel(Tree *From,LEX id);
	int DupControl(Tree* Addr, LEX a);	

	void addStruct(Tree* Addr, Tree* From,Scaner* sc);

	Tree* SemGetTypeStruct(LEX a, Scaner *sc);
	Tree* FindDown(Tree * From, LEX id);

	void SemSetType(Tree *Addr,DATA_TYPE t); 
	Tree * SemGetType(LEX a, Scaner *sc);
	DATA_TYPE getDataType(Tree *Addr);
	char* getSructType();

	
};


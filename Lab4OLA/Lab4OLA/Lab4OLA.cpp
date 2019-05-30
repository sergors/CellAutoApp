// Lab4OLA.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "Scaner.h"
#include "Parser.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "RUS");
	Scaner *sc;
	LEX l;
	int type=0;
	sc = new Scaner("input.txt");
	Parser *p= new Parser(sc);
	p->S();
	type=sc->scaner(l);
	if(type==Tend) cout<<"Ошибок не обнаружено\n";
	else sc->paintError("Лишний текст в программе ",l);
	system("pause");
	
	return 0;
}


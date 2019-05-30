#include "stdafx.h"
#include "Scaner.h"
#include "defs.h"
#include <cctype>

LEX keywords[MAXKEY] =
{
	"float", "char", "bool", "main", "struct", "while", "true", "false"
};
int indexkeywords[MAXKEY] =
{
	Tfloat, Tchar, Tbool, Tmain, Tstruct, Twhile, Ttrue, Tfalse
};

bool t = false;

void Scaner::setUK(int i)
{
	uk=i;
}
void Scaner::setStr(int i)
{
	str=i;
}
void Scaner::setStb(int i)
{
	stb=i;
}
int Scaner::getUK()
{
	return uk;
}
int Scaner::getStr()
{
	return str;
}
int Scaner::getStb()
{
	return stb;
}
Scaner::Scaner(string path)
{
	loadFromFile(path);
	uk = 0;
	str = 1;
	stb = 1;
}

Scaner::~Scaner(void)
{
}

void Scaner::loadFromFile(string path)
{
	ifstream inp(path);
	if(!inp.is_open()) paintError(FileIsNotOpen, "");
	int i;
	for(i = 0; i < MAXTEXT && !inp.eof(); i++)
	{
		text[i] = inp.get();
	}
	text[i-1] = '#';
	inp.close();
}

void Scaner::paintError(char* error, char* l)
{
	int argc;
	if(l[0]=='\0') printf("Ошибка(%d:%d): %s %s\n",str,stb,error,l);
	else printf("Ошибка(%d:%d): %s. Прочитали: %s\n",str,stb,error,l);
	cin>>argc;
	exit(0);
}

int Scaner::scaner(LEX lex)
{
	int i;
	for (i = 0; i < MAXLEX; i++) lex[i] = 0;
	i = 0;

	start:
	//Пропуск незначимых символов
	while (text[uk] == ' ' || text[uk] == '\n' || text[uk] == '\t')
	{
		if (text[uk] == '\n') 
		{
			str++;
			stb = 0;
		}
		else if(text[uk]==' ' || text[uk]=='\t')
		{
			stb++;
		}
		uk++;
	};
	//Пропуск однострочного комментария
	if (text[uk] == '/' && text[uk + 1] == '/')
	{
		uk += 2;
		stb += 2;
		while (text[uk]!='\n'&&text[uk]!='\0')
		{
			stb++;
			uk++;
		}
		if(text[uk]=='\n')
		{
			stb = 1;
			str ++;
			uk ++;
		}
		goto start;
	}
	
	//Идентификатор
q0:	 if (text[uk] >= 'a' && text[uk] <= 'z' ||
		text[uk] >= 'A' &&  text[uk] <= 'Z')
	{
		lex[i++]=text[uk++];
		goto q1;
	}
	 //Константы
	else if (text[uk] >= '1' && text[uk] <= '9') //constfloat не 0
	{
		int lenght=14;
		lex[i++]=text[uk++];
		stb++;
		while(text[uk]>='0' && text[uk]<='9')
		{
			if(i>lenght)
			{
				paintError("Превышена допустимая длина константы ",lex);
				return Terror;
			}
			lex[i++]=text[uk++];
			stb++;
		}
		if(text[uk]!='.')
		{
			paintError("Недопустимый синтаксис вещественной константы",lex);
			return Terror;
		}
		else
		{
			lex[i++]=',';uk++;
			stb++;
			if(text[uk]>='0' && text[uk]<='9')
			{
				while(text[uk]>='0' && text[uk]<='9')
				{
					if(i>lenght)
					{
						paintError("Превышена допустимая длина константы ",lex);
						while((text[uk]>='0' && text[uk]<='9') || text[uk]=='.')
						{
							uk++;
						}
						return Terror;
					}
					lex[i++]=text[uk++];
					stb++;
				}
			}
			else
			{
				paintError("Недопустимый синтаксис вещественной константы ",lex);
				return Terror;
			}
			
	
		}
		return Tconstfloat;

	}
	else if (text[uk] == '0') //constfloat 0
	{
		lex[i++]=text[uk++];
		stb++;
		if(text[uk]!='.')
		{
			paintError("Допускаются только десятеричные константы", lex);
			uk++;
			while((text[uk]>='0' && text[uk]<='9') || text[uk]=='.')
			{
				uk++;
			}
			return Terror;
		}
		else
		{
			lex[i++]=',';uk++;
			stb++;
			int lenght=11;
			while(text[uk]>='0' && text[uk]<='9')
			{
				if(i>lenght)
				{
					paintError("Превышена допустимая длина константы ",lex);
					while(text[uk]>='0' && text[uk]<='9')
					{
						uk++;
					}
					return Terror;
				}
				lex[i++]=text[uk++];
				stb++;
			}
			return Tconstfloat;
		}
	}
	else if ((text[uk] == '\'')&&(text[uk+2] == '\'')) //символьная
	{
		lex[i++]=text[uk++];
		goto q3;
	}
	else if(text[uk] == '=')
		{
			lex[i++] = text[uk++];
			stb++;
			return Travno;
		}
	else if(text[uk] == '+')
		{
			lex[i++] = text[uk++];
			stb++;
			return Tplus;
		}
	else if(text[uk] == '-')
		{
			lex[i++] = text[uk++];
			stb++;
			return Tminus;
		}

	else if(text[uk]=='/')
	{
		lex[i++] = text[uk++];
		stb++;
		return Tdiv;
	}
	else if(text[uk]=='*')
	{
		lex[i++] = text[uk++];
		stb++;
		return Tmul;
	}
	else if (text[uk] == '#'){
		lex[0]=text[uk];
		return Tend; //конец исходного текста
	}
	else if(text[uk]==',')
	{
		lex[i++] = text[uk++];
		stb++;
		return Tcomma;
	}
	else if(text[uk]==';')
	{
		lex[i++] = text[uk++];
		stb++;
		return Tsemicolon;
	}
	else if(text[uk]=='{')
	{
		lex[i++] = text[uk++];
		stb++;
		return Topenblock;
	}

	else if(text[uk]=='}')
	{
		lex[i++] = text[uk++];
		stb++;
		return Tcloseblock;
	}

	else if(text[uk]=='(')
	{
		lex[i++] = text[uk++];
		stb++;
		return Topenbracket;
	}

	else if(text[uk]==')')
	{
		lex[i++] = text[uk++];
		stb++;
		return Tclosebracket;
	}
	else if(text[uk]=='.')

	{
		lex[i++] = text[uk++];
		stb++;
		return Tpoint;
	}

	else if(text[uk]=='!')
	{
		lex[i++] = text[uk++];
		stb++;
		return TNe;
	}
	else if(text[uk]=='|')
	{
		lex[i++] = text[uk++];
			stb++;
		if (text[uk] == '|')
		{
			lex[i++] = text[uk++];
			stb++;
			return TIli;
		}
		else
		{
			paintError("Неизвестный символ ",lex);
			return Terror;
		}

	}
	else if(text[uk]=='&')
	{
		lex[i++] = text[uk++];
			stb++;
		if (text[uk] == '&')
		{
			lex[i++] = text[uk++];
			stb++;
			return TI;
		}
		else
		{
			paintError("Неизвестный символ ",lex);
			
			return Terror;
		}
	}

	else
	{
		paintError(InvalidCharacter, lex);
		uk++;
		return Terror;
	}
q1: while (text[uk] >= 'a' && text[uk] <= 'z' ||
			text[uk] >= 'A' &&  text[uk] <= 'Z' ||
			text[uk] >= '0' && text[uk] <= '9' ||
			text[uk] == '_')
			if (i < MAXLEX - 1) 
			{
				lex[i++] = text[uk++];
				stb++;
			}
			else 
			{ 
				while (text[uk] >= 'a' && text[uk] <= 'z' ||
			text[uk] >= 'A' &&  text[uk] <= 'Z' ||
			text[uk] >= '0' && text[uk] <= '9' ||
			text[uk] == '_'){uk++; 
				stb++; 
				}
				paintError(LenthOfConstant, lex);
				return Terror;
			};
		for(int i = 0; i < MAXKEY; i++)
		{
			if (strcmp(keywords[i], lex) == 0) //обе строки равны
				return indexkeywords[i];
		}
		return Tid;
q3:     stb++;
		while (text[uk] >= 'a' && text[uk] <= 'z' ||
			text[uk] >= 'A' &&  text[uk] <= 'Z' ||
			text[uk] >= '0' && text[uk] <= '9' ||
			text[uk] >= '!' && text[uk] <= '%' ||
			text[uk] == '_' || text[uk]=='\'')
		{ 
			if (i < MAXLEX - 1) 
			{
				lex[i++] = text[uk++];
				stb++;
			}
			else 
			{
				paintError(LenthOfConstant, lex);
				return Terror;
			}
		}
		return Tconschar;
}
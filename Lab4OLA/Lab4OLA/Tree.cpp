#include "stdafx.h"
#include "Tree.h"
#include <string.h>
#define max(a,b) a<b? b:a
Tree* Tree::Cur=(Tree*)NULL;
Tree::Tree()
{
	n=new Node();
	Up=NULL; Left=NULL; Right=NULL;
	memcpy(n,&("------"),sizeof(Node));
}
Tree::Tree(Tree *l, Tree *r, Tree *u, Node *d)
{
	n=new Node();
	Up=u; Left=l; Right=r;
	memcpy(n,d,sizeof(Node));
}
Tree* Tree::CreateEmpty()
{
	Tree* v;
	Node *b= new Node();
	v=this->Cur;
	strcpy_s(b->id,"empty node");
	b->DataType=TYPE_EMPTY;
	this->Cur->setRight(b);
	this->Cur=this->Cur->Right;
	return v;
}
Tree* Tree::SemInclude(LEX a, DATA_TYPE t, Scaner *sc)
{
	if(DupControl(Cur,a))
	{
		sc->paintError("Повторное описание идентификатора ",a);
	}
	Tree *v;
	Node b;
	memcpy(b.id,a,strlen(a)+1);
	b.DataType=t;
	b.TYPE=NULL;
	Cur->setLeft(&b); //сделали вершину - переменную
	Cur= Cur->Left; //переместились на нее
	return Cur;
}
Tree* Tree::SemInclude(LEX a, char* t, Scaner *sc)
{
	if(DupControl(Cur,a))
	{
		sc->paintError("Повторное описание идентификатора ",a);
	}
	Tree *v;
	Node b;
	memcpy(b.id,a,strlen(a)+1);
	b.DataType=TYPE_STRUCT;
	b.TYPE=t;
	Cur->setLeft(&b); //сделали вершину - переменную
	Cur= Cur->Left; //переместились на нее
	return Cur;
}

void Tree::addStruct(Tree* Addr, Tree* From, Scaner *sc)
{
	LEX lex;
	DATA_TYPE type;
	char * struct_type;
	LEX id;
	Tree* i=Addr;
	Tree* tmp;
	i=i->Right;
	Tree* j=From;
	while(i!=NULL)
	{
		if(i->Left!=NULL)
		{
			if(i->Left->n->DataType==TYPE_STRUCT)
			{
				strcpy(id,i->Left->n->TYPE);
				tmp=i->FindUp(i->getCur(),id);
				if(tmp!=NULL)
				{
					j->SemInclude(i->Left->n->id,i->Left->n->TYPE,sc);
					j->CreateEmpty();
					j=j->getCur();
					addStruct(tmp,j,sc);
					break;
				}
				else
				{
					cout<<endl<<"Ошибка при создании объекта структуры"<<endl;
					exit(0);
				}
			}
				//j->Left->n=i->Left->n;
				j->SemInclude(i->Left->n->id,i->Left->n->DataType,sc);
				j=j->Left;
				i=i->Left;
		}
		else
		{
			i=i->Left;
		}
	}

}
void Tree::setLeft(Node *Data)
{
	Tree *a= new Tree(NULL,NULL,this,Data);
	Left=a;
}
void Tree::setRight(Node *Data)
{
	Tree * a = new Tree(NULL,NULL,this,Data);
	Right=a;
}
void Tree::setCur(Tree *a)
{
	Cur=a;
}
Tree* Tree::getCur()
{
	return Cur;
}

Tree* Tree::FindUp(Tree *From, LEX id)
{
	Tree * i=From;
	while((i!=NULL)&&(memcmp(id,i->n->id,max(strlen(i->n->id),strlen(id)))!=0))
	{
		i=i->Up;
	}
	return i;
}
Tree* Tree::FindUpOneLevel(Tree *From,LEX id)
{
	Tree *i=From;
	int j=0;
	while(i!=NULL)
	{		
		if(this->getDataType(i)==TYPE_EMPTY) return NULL;

		if(memcmp(id,i->n->id,max(strlen(i->n->id),strlen(id)))==0)	return i; //если есть такой то возвращаем его

		i=i->Up;	
	}
	return NULL;
}
int Tree::DupControl(Tree* Addr, LEX a)
{
	if (FindUpOneLevel(Addr,a)==NULL) return 0;
	else return 1;
}

void Tree::SemSetType(Tree *Addr,DATA_TYPE t)
{
	Addr->n->DataType=t;
}
Tree * Tree::SemGetType(LEX a, Scaner *sc)
{
	Tree * v=FindUp(Cur,a);
	if(v==NULL) sc->paintError("Отсутствует описание ид-ра",a);
	return v;
}
Tree* Tree::SemGetTypeStruct(LEX a, Scaner *sc)
{
	Tree *v=FindDown(Cur,a);
	if(v==NULL) sc->paintError("Отсутствует описание ид-ра",a);
	return v;
}
Tree* Tree::FindDown(Tree * From, LEX id)
{
	Tree * t=From->Right;
	if(t->Left==NULL) 
		return NULL;
	else 
		t=t->Left; 

	while((t!=NULL)&&(memcmp(id,t->n->id,max(strlen(t->n->id),strlen(id)))!=0))
	{
		t=t->Left;
	}
	return t;
}
DATA_TYPE Tree::getDataType(Tree *Addr)
{
	return Addr->n->DataType;
}
char* Tree::getSructType()
{
	return this->n->TYPE;
}

float Tree::getDataFloat()
{
	return this->n->DataValue.data_float;
}
char Tree::getDataChar()
{
	return this->n->DataValue.data_char;
}
bool Tree::getDataBool()
{
	return this->n->DataValue.data_bool;
}
void Tree::setDataFloat(LEX zn)
{
	this->n->DataValue.data_float=atof(zn);
}
void Tree::setDataFloat(float n)
{
	this->n->DataValue.data_float=n;
}

void Tree::setDataChar(LEX zn)
{
	this->n->DataValue.data_char=zn[1];
}
void Tree::setDataChar(char n)
{
	this->n->DataValue.data_char=n;
}

void Tree::setDataBool(LEX zn)
{
	if(zn=="true")
		this->n->DataValue.data_bool=true;
	else if(zn=="false")
		this->n->DataValue.data_bool=false;
}
void Tree::setDataBool(bool n)
{
	this->n->DataValue.data_bool=n;
}

char* Tree::getId()
{
	return this->n->id;
}
Tree::~Tree()
{
}

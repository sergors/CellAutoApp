#include "stdafx.h"
#include "Parser.h"


Parser::Parser(Scaner *s)
{
	scan=s;
	Root = new Tree();
	Root->setCur(Root);
	FlInt=1;
}
void Parser::S()
{
	LEX l;
	int t,uk1,str1,stb1;
	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	while(t==Tfloat || t==Tbool || t==Tchar || t==Tstruct || t==Tid)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
		OpisaniePeremenn();
		uk1=scan->getUK();
		str1=scan->getStr();
		stb1=scan->getStb();
		t=scan->scaner(l);
	}
	if(t!=Tmain) scan->paintError("�������� main ",l);
	t=scan->scaner(l);
	if(t!=Topenbracket) scan->paintError("��������� ( ����� main ",l);
	t=scan->scaner(l);
	if(t!=Tclosebracket) scan->paintError("��������� ) ����� main( ",l);
	Block();
}
void Parser::OpisaniePeremenn()
{
	LEX l;
	LEX l_tmp;
	int t,uk1,str1,stb1;
	char *struct_type=new char[15];
	
	t=scan->scaner(l);
	Tree *tmp;
	if(t==Tfloat || t==Tchar || t==Tbool || t==Tid)
	{
														//���������
		if(t==Tfloat) type=TYPE_FLOAT;
		if(t==Tbool) type=TYPE_BOOL;
		if(t==Tchar) type=TYPE_CHAR;
		if(t==Tid)
		{
			tmp=Root->FindUp(Root->getCur(),l);
			if(tmp==NULL) scan->paintError("������ ���� �� ����������",l);
			else
			{
				type=TYPE_STRUCT;
				strcpy(struct_type,l);
			}
		}
														//����� ���������
		do
		{
			t=scan->scaner(l);
			if(t!=Tid) scan->paintError("�������� ������������� � �������� ���������� ",l);
			//���������
			Tree *v;
			Tree* temp;
			if(type==TYPE_STRUCT) 
			{

				v=Root->SemInclude(l,struct_type,scan);//������� �������������(�-� ����� ��������� �� ������)
				temp=v;//&
				Root->CreateEmpty(); //c��������(�������� ������ ����� ��� ����� ���������)		
				Root->addStruct(tmp,Root->getCur(),scan);
				Root->setCur(temp);//&

			}
			else
				v=Root->SemInclude(l,type,scan);
			t=scan->scaner(l);
			if(t==Travno)
			{
				t=scan->scaner(l);
				if(t!=Tconschar && t!=Tconstfloat && t!=Ttrue && t!=Tfalse)
					scan->paintError("��� �������� ���������� ��������� ��������� ��� true ��� false ����� =  ",l);
				//���������
				DATA_TYPE constType;
				if(t==Tconschar) constType=TYPE_CHAR;
				if(t==Tconstfloat) constType=TYPE_FLOAT;
				if(t==Ttrue || t==Tfalse) constType=TYPE_BOOL;
				if(v->getDataType(v)!=constType) scan->paintError("��� ��������� �� ������������� ���� �������������� ","");

				if(t==Tconschar)
					v->setDataChar(l);
				else if(t==Tconstfloat)
					v->setDataFloat(l);
				else if(t==Ttrue || t==Tfalse)
					v->setDataBool(l);
				else scan->paintError("����������� ��������� ��� �������������",l);

				if(t==Tconschar)
					cout<<v->getId()<<"="<<v->getDataChar()<<endl;
				else if(t==Tconstfloat)
					cout<<v->getId()<<"="<<v->getDataFloat()<<endl;
				else if(t==Ttrue || t==Tfalse)
					cout<<v->getId()<<"="<<v->getDataBool()<<endl;

				t=scan->scaner(l);
			}
			
		}while(t==Tcomma);
		if(t!=Tsemicolon) scan->paintError(" ��������� ; � �������� ���������� ",l);
	}
	else if(t==Tstruct)
	{
		
		 type=TYPE_STRUCT;//���������

		t=scan->scaner(l);
		if(t!=Tid) scan->paintError(" �������� ������������� ��������� � �������� ��������� ",l);
		Tree *v=Root->SemInclude(l,type,scan); //���������
		t=scan->scaner(l);
		if(t!=Topenblock) scan->paintError(" ��������� {  � �������� ��������� ",l);

		
		Root->CreateEmpty(); //c��������(�������� ������ ����� ��� ����� ���������)

		do
		{
			t=scan->scaner(l);
			if(t!=Tfloat && t!=Tchar && t!=Tbool && t!=Tid) scan->paintError(" �������� ��� � �������� ����� ��������� ",l);
			//���������
			if(t==Tfloat) type=TYPE_FLOAT;
			if(t==Tbool) type=TYPE_BOOL;
			if(t==Tchar) type=TYPE_CHAR;
		    if(t==Tid)
		    {
			    tmp=Root->FindUp(Root->getCur(),l);
			    if(tmp==NULL) scan->paintError("������ ���� �� ����������",l);
			    else
			    {
				   type=TYPE_STRUCT;
				   strcpy(struct_type,l);
			    }
		     }
			
			t=scan->scaner(l);
			if(t!=Tid) scan->paintError(" �������� ������������� � �������� ����� ��������� " ,l);
			
			Tree *v1;
			if(type==TYPE_STRUCT) v1=Root->SemInclude(l,struct_type,scan);
			else v1=Root->SemInclude(l,type,scan); //������� ���� ���������
     		t=scan->scaner(l);
			if(t!=Tsemicolon) scan->paintError(" ��������� ; � �������� ����� ��������� ",l);
			uk1=scan->getUK();
			str1=scan->getStr();
			stb1=scan->getStb();
			t=scan->scaner(l);
			scan->setUK(uk1);
			scan->setStr(str1);
			scan->setStb(stb1);
		}while(t==Tfloat || t==Tchar || t==Tbool || t==Tid);
		t=scan->scaner(l);
		if(t!=Tcloseblock) scan->paintError(" ��������� }  � �������� ��������� ",l);

		Root->setCur(v);//���������(����� �� ���� ���������)

		t=scan->scaner(l);
		if(t!=Tsemicolon) scan->paintError(" ��������� ; � ����� �������� ��������� ",l);
	}
	else scan->paintError("� �������� ���������� �������� ��� float, char, bool ���  struct ",l);
}
void Parser::Block()
{
	LEX l;
	int t,uk1,str1,stb1;

	Tree* v=Root->getCur();
	Root->CreateEmpty(); //�������� ������� ����

	t=scan->scaner(l);
	if(t!=Topenblock) scan->paintError(" ��������� { � ����� ",l);
	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	while(t==Tsemicolon || t==Tid || t==Twhile || t==Topenblock || t==Tfloat || t==Tchar || t==Tbool)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
		Operator();
		uk1=scan->getUK();
		str1=scan->getStr();
		stb1=scan->getStb();
		t=scan->scaner(l);
	}
	if(t!=Tcloseblock) scan->paintError(" ��������� } � ����� ����� ",l);

	
	Root->setCur(v); //�����
}
void Parser::Operator()
{
	LEX l;
	int t,uk1,str1,stb1;
	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	if(t==Tid)
	{
		Tree *v=Root->FindUp(Root->getCur(),l);
		if(v==NULL) scan->paintError("������������� �������������",l);
		if(v->getDataType(v)==TYPE_STRUCT && v->getSructType()==NULL)
		{
			scan->setUK(uk1);
			scan->setStr(str1);
			scan->setStb(stb1);
			OpisaniePeremenn();
		}
		else
		{
			scan->setUK(uk1);
			scan->setStr(str1);
			scan->setStb(stb1);
		    Prisvaivanie();
		}
	}
	else if(t==Twhile)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
		While();
	}
	else if(t==Topenblock)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
		Block();
	}
	else if(t==Tfloat || t==Tchar || t==Tbool)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
		OpisaniePeremenn();
	}
	else if(t!=Tsemicolon)
	{
		scan->paintError(" �������� ����� �������� ",l);
	}
}
void Parser::Prisvaivanie()
{
	LEX l,l1;
	int t,uk1,str1,stb1;
	string s="";
	char databuf_char;
	bool databuf_bool;
	float databuf_float;

	t=scan->scaner(l);
	if(t!=Tid) scan->paintError(" �������� ������������� � ������������ ",l);
	s+=l;
	Tree *v=Root->SemGetType(l,scan); //���������(����� ��-�� � ������ � ����������� ��� ����)
	t=scan->scaner(l);
	if(v->getDataType(v)==TYPE_STRUCT) s+=l;
	Tree *oldCur=Root->getCur();
	while(t==Tpoint)
	{
		t=scan->scaner(l);
		if(t!=Tid) scan->paintError("� ������������ �������� ������������� ���� ��������� ",l);
		s+=l;
		if(v->getDataType(v)!=TYPE_STRUCT) scan->paintError("��-� ����� ������ �� ���� ��������� ","");
	//	strcpy(l1,v->getSructType());
		//v=Root->SemGetType(l1,scan);
		Root->setCur(v);
		v=Root->SemGetTypeStruct(l,scan);
		Root->setCur(oldCur);
		t=scan->scaner(l);
		if(t==Tpoint) s+=l;
	}
	if(t!=Travno) scan->paintError("� ������������ ��������� = ",l);
	DATA_TYPE value;
	value=Viragenie();

	databuf_bool=this->data_bool;
	databuf_char=this->data_char;
	databuf_float=this->data_float;


	if(v->getDataType(v)==TYPE_STRUCT || value==TYPE_STRUCT) scan->paintError("������������ �������� �� ����������","");
	if(v->getDataType(v)!=value) 
		scan->paintError("��� �������������� ��������� �� ������������� ���� �������","");
	if(this->FlInt)
	{
		if(value==TYPE_FLOAT)
		{
			v->setDataFloat(databuf_float);
			cout<<s<<"="<<boolalpha<<v->getDataFloat()<<endl;
		}
		else if(value==TYPE_BOOL)
		{
			v->setDataBool(databuf_bool);
			cout<<s<<"="<<v->getDataBool()<<endl;
		}
		else if(value==TYPE_CHAR)
		{
			v->setDataChar(databuf_char);
			cout<<s<<"="<<v->getDataChar()<<endl;
		}
	}
	t=scan->scaner(l);
	if(t!=Tsemicolon) scan->paintError(" � ����� ������������ ��������� ; ",l);
}
void Parser::While()
{
	LEX l;
	int t,uk1,str1,stb1;
	char databuf_char;
	bool databuf_bool;
	float databuf_float;
	int LocFl;
	LocFl=this->FlInt;
	DATA_TYPE type;
	t=scan->scaner(l);
	if(t!=Twhile) scan->paintError("�������� while  ",l);
	t=scan->scaner(l);
	if(t!=Topenbracket) scan->paintError(" ��������� ( ����� while ",l);
	//��������� ��������� ��� ��������
	metka:
	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();

	type=Viragenie();
	if(LocFl==1 && type==TYPE_BOOL)
	{
		databuf_bool=this->data_bool;
	}
	else if(LocFl==1 && type==TYPE_FLOAT)
	{
		databuf_float=this->data_float;
	}

	if(type==TYPE_STRUCT || type==TYPE_CHAR) scan->paintError("������������ �������� � �������","");
	t=scan->scaner(l);
	if(t!=Tclosebracket) scan->paintError(" ��������� ) ����� while(��������� ",l);
	if(LocFl==1 && type==TYPE_BOOL && databuf_bool==true || LocFl==1 && type==TYPE_FLOAT && databuf_float>0)
	{
		this->FlInt=1;
	}
	else
	{
		this->FlInt=0;
	}
	Operator();
	if(this->FlInt==1)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
		goto metka;
	}
	this->FlInt=LocFl;
}
DATA_TYPE Parser::Viragenie()
{
	LEX l;
	int t,uk1,str1,stb1;
	DATA_TYPE type1,type2=TYPE_EMPTY;

	char databuf_char1,databuf_char2;
	bool databuf_bool1,databuf_bool2;
	float databuf_float1,databuf_float2;

	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	if(t!=Tplus && t!=Tminus)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
	}
	type1=V1();
	databuf_bool1=this->data_bool;
	databuf_char1=this->data_char;
	databuf_float1=this->data_float;
	if(type1!=TYPE_FLOAT &&(t==Tplus || t==Tminus)) scan->paintError("������������ ������� �������� � ����������","");
	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	while(t==TI || t==TIli)
	{
		databuf_bool1=this->data_bool;
		databuf_char1=this->data_char;
		databuf_float1=this->data_float;
		type2=V1();
		databuf_bool2=this->data_bool;
		databuf_char2=this->data_char;
		databuf_float2=this->data_float;
		if(type2==TYPE_CHAR || type1!=type2) scan->paintError("������������ ���������� �������� � �����������","");

		if(this->FlInt)
		{
			if(type1==TYPE_FLOAT && t==TI)
			{
				this->data_bool=(bool)(databuf_float1 && databuf_float2);
			}
			else if(type1==TYPE_FLOAT && t==TIli)
			{
				this->data_bool=(bool)(databuf_float1 || databuf_float2);
			}
			else if(type1==TYPE_BOOL && t==TI)
			{
				this->data_bool=(databuf_bool1 && databuf_bool2);
			}
			else if(type1==TYPE_BOOL && t==TIli)
			{
				this->data_bool=(databuf_bool1 || databuf_bool2);
			}
		}

		uk1=scan->getUK();
		str1=scan->getStr();
		stb1=scan->getStb();
		t=scan->scaner(l);
		type1=TYPE_BOOL;
	}
	scan->setUK(uk1);
	scan->setStr(str1);
	scan->setStb(stb1);
	if(type2!=TYPE_EMPTY) return TYPE_BOOL;
	else return type1;

}
DATA_TYPE Parser::V1()
{
	LEX l;
	int t,uk1,str1,stb1;
	DATA_TYPE type;

	char databuf_char;
	bool databuf_bool;
	float databuf_float;

	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	if(t!=TNe)
	{
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
	}

	type=V2();
	databuf_bool=this->data_bool;
	databuf_char=this->data_char;
	databuf_float=this->data_float;
	if(t==TNe && type==TYPE_CHAR) scan->paintError("������������ ��������  !  ��� ����������","");
	if(t==TNe && this->FlInt)
	{
		if(type==TYPE_BOOL)
		{
			this->data_bool=!databuf_bool;
		}
		else if(type==TYPE_FLOAT)
		{
			this->data_bool=!(bool)databuf_float;
		}
	}
	return type;
}
DATA_TYPE Parser::V2()
{
	LEX l;
	int t,uk1,str1,stb1;
	DATA_TYPE type1, type2;

	char databuf_char1,databuf_char2;
	bool databuf_bool1,databuf_bool2;
	float databuf_float1,databuf_float2;

	type1=V3();
	databuf_bool1=this->data_bool;
	databuf_char1=this->data_char;
	databuf_float1=this->data_float;
	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	while(t==Tplus || t==Tminus)
	{
		databuf_bool1=this->data_bool;
		databuf_char1=this->data_char;
		databuf_float1=this->data_float;
		type2=V3();
		databuf_bool2=this->data_bool;
		databuf_char2=this->data_char;
		databuf_float2=this->data_float;

		if(type2!=TYPE_FLOAT || type1!=TYPE_FLOAT) scan->paintError("������������ ��������(+ ��� -) �������� ��� ����������","");
		uk1=scan->getUK();
		str1=scan->getStr();
		stb1=scan->getStb();


		if(this->FlInt)
		{
			if(type1==TYPE_FLOAT && t==Tplus)
			{
				this->data_float=databuf_float1+databuf_float2;
			}
			else if(type1==TYPE_FLOAT && t==Tminus)
			{
				this->data_float=databuf_float1 - databuf_float2;
			}
			else
			{
				scan->paintError("��� ������������� ��������-��������� ��������� ������","");
			}
	
		}

		t=scan->scaner(l);
	}
	scan->setUK(uk1);
	scan->setStr(str1);
	scan->setStb(stb1);

	return type1;
}
DATA_TYPE Parser::V3()
{
	DATA_TYPE type1, type2;
	LEX l;

	char databuf_char1,databuf_char2;
	bool databuf_bool1,databuf_bool2;
	float databuf_float1,databuf_float2;
	int t,uk1,str1,stb1;


	type1=V4();
	databuf_bool1=this->data_bool;
	databuf_char1=this->data_char;
	databuf_float1=this->data_float;
	uk1=scan->getUK();
	str1=scan->getStr();
	stb1=scan->getStb();
	t=scan->scaner(l);
	while(t==Tmul || t==Tdiv)
	{
		databuf_bool1=this->data_bool;
		databuf_char1=this->data_char;
		databuf_float1=this->data_float;
		type2=V4();
		databuf_bool2=this->data_bool;
		databuf_char2=this->data_char;
		databuf_float2=this->data_float;
		if(type2!=TYPE_FLOAT || type1!=TYPE_FLOAT) scan->paintError("������������ �������� (* ��� /) �������� ��� ����������","");

		if(this->FlInt)
		{
			if(type1==TYPE_FLOAT && t==Tmul)
			{
				this->data_float=databuf_float1*databuf_float2;
			}
			else if(type1==TYPE_FLOAT && t==Tdiv)
			{
				this->data_bool=databuf_float1 / databuf_float2;
			}
			else
			{
				scan->paintError("��� ������������� ���-����. ��������� ������","");
			}
	
		}

		uk1=scan->getUK();
		str1=scan->getStr();
		stb1=scan->getStb();
		t=scan->scaner(l);
	}
	scan->setUK(uk1);
	scan->setStr(str1);
	scan->setStb(stb1);

	return type1;
}
DATA_TYPE Parser::V4()
{
	LEX l,l1;
	int t,uk1,str1,stb1;
	DATA_TYPE type_idr, type_value;
	t=scan->scaner(l);
	if(t!=Tid && t!=Tconschar && t!=Tconstfloat && t!=Ttrue && t!=Tfalse && t!=Topenbracket)
		scan->paintError("� ������������ ��������� ��������� idr ��� ��������� ��� true false  ��� ( ",l);
	if(t==Tid)
	{
		Tree *v=Root->SemGetType(l,scan);
		Tree *oldCur=Root->getCur();
		if(v->getDataType(v)==TYPE_STRUCT && v->getSructType()==NULL) scan->paintError("������������ �������� � ������ ���������","");
		uk1=scan->getUK();
		str1=scan->getStr();
		stb1=scan->getStb();
		t=scan->scaner(l);
		while(t==Tpoint)
		{
			t=scan->scaner(l);
			if(t!=Tid) scan->paintError(" �������� ������������� ���� ��������� ����� ����� ",l);
			if(v->getDataType(v)!=TYPE_STRUCT) scan->paintError("��-� ����� ������ �� ���� ��������� ","");
			strcpy(l1,v->getId());
			v=Root->FindUp(v,l1);
			Root->setCur(v);
			v=Root->SemGetTypeStruct(l,scan);
			Root->setCur(oldCur);
			uk1=scan->getUK();
			str1=scan->getStr();
			stb1=scan->getStb();
			t=scan->scaner(l);
		}
		scan->setUK(uk1);
		scan->setStr(str1);
		scan->setStb(stb1);
		type_idr=v->getDataType(v);
		if(type_idr==TYPE_STRUCT) scan->paintError("������������ �������� �� ����������","");
		if(this->FlInt)
		{
			if(type_idr==TYPE_FLOAT)
				this->data_float=v->getDataFloat();
			else if(type_idr==TYPE_BOOL)
				this->data_bool=v->getDataBool();
			else if(type_idr==TYPE_CHAR)
				this->data_char=v->getDataChar();
			else 
				scan->paintError("��� ������������� ��. ���. ��������� ������","");
		}
		return type_idr;
	}
	else if(t==Topenbracket)
	{
		type_value=Viragenie();
		t=scan->scaner(l);
		if(t!=Tclosebracket) scan->paintError(" ��������� ) ����� (��������� ",l);
		return type_value;
	}
	else
	{
		if(t==Ttrue || t==Tfalse)
		{
			type_value=TYPE_BOOL;
			if(this->FlInt && l[0]=='t')
				this->data_bool=true;
			else if(this->FlInt && l[0]=='f')
				this->data_bool=false;
		}
		if(t==Tconstfloat)
		{
			type_value=TYPE_FLOAT;
			if(this->FlInt)
				this->data_float=atof(l);
		}
		if(t==Tconschar)
		{
			type_value=TYPE_CHAR;
			if(this->FlInt)
				this->data_char=l[0];
		}

		return type_value;
	}

}


Parser::~Parser(void)
{
}

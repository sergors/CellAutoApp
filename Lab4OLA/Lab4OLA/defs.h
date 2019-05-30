#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAXLEX 20
#define MAXKEY 9
#define MAXTEXT 1000
typedef char LEX[MAXLEX];
typedef char TEXT[MAXTEXT]; //����� ��������� ����

//�������������
#define Tid			1

//�������� �����
#define Tfloat 2
#define Tchar 3
#define Tbool 4
#define Tmain 5
#define Tstruct 6
#define Twhile 7
#define Ttrue 22
#define Tfalse 23

//������
#define Topenblock	10
#define Tcloseblock	11
#define Topenbracket	8
#define Tclosebracket	9

//�����������
#define Tcomma		12 //�������
#define Tsemicolon	13 //����� � �������
#define Tpoint      26 //�����

//��������
#define Tplus		14
#define Tminus		15
#define Tmul		16
#define Tdiv		17
#define Travno		18
#define TNe			19
#define TIli		20
#define TI			21

//���������
#define Tconstfloat 24
#define Tconschar 25

//����� ��������� ������
#define Tend		100

//��������� �������
#define Terror		200

//��������� �� �������
#define InvalidCharacter "����������� ������"
#define LenthOfConstant "����� ��������� ��������� ����������"
#define ConstFloatError "����������� ������ ������������ ���������"
#define FileIsNotOpen "�� ������� ������� ����"
#define ErrorLex "����������� � ���������������� ���������"
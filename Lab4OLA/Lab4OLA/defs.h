#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAXLEX 20
#define MAXKEY 9
#define MAXTEXT 1000
typedef char LEX[MAXLEX];
typedef char TEXT[MAXTEXT]; //текст исходного кода

//Идентификатор
#define Tid			1

//Ключевые слова
#define Tfloat 2
#define Tchar 3
#define Tbool 4
#define Tmain 5
#define Tstruct 6
#define Twhile 7
#define Ttrue 22
#define Tfalse 23

//Скобки
#define Topenblock	10
#define Tcloseblock	11
#define Topenbracket	8
#define Tclosebracket	9

//Разделители
#define Tcomma		12 //запятая
#define Tsemicolon	13 //точка с запятой
#define Tpoint      26 //точка

//Операции
#define Tplus		14
#define Tminus		15
#define Tmul		16
#define Tdiv		17
#define Travno		18
#define TNe			19
#define TIli		20
#define TI			21

//константы
#define Tconstfloat 24
#define Tconschar 25

//Конец исходного модуля
#define Tend		100

//Ошибочная лексема
#define Terror		200

//Сообщения об ошибках
#define InvalidCharacter "Неизвестный символ"
#define LenthOfConstant "Длина константы превышает допустимую"
#define ConstFloatError "Неправильно задана вещественная константа"
#define FileIsNotOpen "Не удалось открыть файл"
#define ErrorLex "Закончилось в незаключительном состоянии"
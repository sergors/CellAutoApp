#include "scaner.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

LEX keywords[MAXKEY] =
{
    "var", "int", "bool", "neig", "ClassArray", "CellAuto", "System"
};
int indexkeywords[MAXKEY] =
{
  t_var, t_int, t_bool, t_neig, t_class_array, t_cell_auto, t_system
};

Scaner::Scaner(char* path)
{
    loadFile(path);
    pointer = 0;
    row = 1;
    column = 1;
}
Scaner::Scaner(const char* text)
{
    strcpy(this->text, text);
    pointer = 0;
    row = 1;
    column = 1;
}
Scaner::~Scaner(){}

void Scaner::setPointer(int pointer)
{
    this->pointer = pointer;
}
int Scaner::getPointer()
{
    return this->pointer;
}
void Scaner::setRow(int row)
{
    this->row = row;
}
int Scaner::getRow()
{
    return this->row;
}
void Scaner::setColumn(int column)
{
    this->column = column;
}
int Scaner::getColumn()
{
    return this->column;
}

void Scaner::loadFile(char* path)
{
    ifstream inputStream(path);
    unsigned int i = 0;
    if(inputStream)
    {
        do {
            this->text[i++] = inputStream.get();
        }while (!inputStream.eof());
        this->text[i-1] = '$';
        inputStream.close();
    }
    else
    {
        string fileName(path);
        throw runtime_error("error open file with name = " + fileName);
    }
}

void Scaner::loadFromGUI()
{

}

void Scaner::showError(char* err, char* a)
{
    int argc;
    if(a[0]=='\0') printf("Ошибка(%d:%d): %s %s\n",this->column,this->column,err,a);
    else printf("Ошибка(%d:%d): %s. Прочитали: %s\n",this->column,this->column,err,a);
    cin>>argc;
    exit(0);
}

int Scaner::doScan(LEX lex)
{
    for(int i=0; i< MAXLEX;i++) lex[i] = '\0';

    start:
    //skip spec symbols
    while(text[pointer] == ' ' ||
          text[pointer] == '\n' ||
          text[pointer] == '\t')
    {
        if(text[pointer] == '\t' || text[pointer] == ' ')
            this->column++;

        if(text[pointer] == '\n')
            this->row++;

        pointer++;
    }
    //skip one row comment
    if(text[pointer] == '/' && text[pointer+1] == '/')
    {
        pointer+=2;
        column+=2;
        while(text[pointer]!='\n' && text[pointer] != '\0')
        {
            column++;
            pointer++;
        }
        if(text[pointer] == '\n')
        {
            column = 1;
            row++;
            pointer++;
        }
        goto start;
    }
    //identificator
    if((text[pointer] >= 'a' && text[pointer] <='z') ||
       (text[pointer] >= 'A' && text[pointer] <='Z') ||
            text[pointer] == '_')
    {
        unsigned int i=0;
        lex[i++] = this->text[pointer++];
        column++;

        while((text[pointer] >= 'a' && text[pointer] <= 'z') ||
              (text[pointer] >= 'A' && text[pointer] <= 'Z') ||
              (text[pointer] >= '0' && text[pointer] <= '9') ||
              text[pointer] == '_')
        {
            if(i<MAXLEX - 1) {
                lex[i++] = text[pointer++];
                column++;
            }
            else
            {
                while((text[pointer] >= 'a' && text[pointer] <= 'z') ||
                      (text[pointer] >= 'A' && text[pointer] <= 'Z') ||
                      (text[pointer] >= '0' && text[pointer] <= '9') ||
                      text[pointer] == '_')
                {
                    lex[i++] = text[pointer++];
                    column++;
                }
                showError("Превышена максимально допустимая длина идентификатора", lex);
                return t_error;
            }
        }
        for(int i = 0; i < MAXKEY; i++)
        {
            if(strcmp(keywords[i], lex) == 0)
                return indexkeywords[i];
        }
        return t_id;

    }
}

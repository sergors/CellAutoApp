#include "scaner.h"
#include <map>
#include <fstream>

static map<int, LEX> keywords = {
    {t_int, "int"},
    {t_bool, "bool"},
    {t_neig, "neig"},
    {t_system, "System"},
    {t_class_array, "classArray"},
    {t_cell_auto, "cellAuto"},
    {t_var, "var"}
};

Scaner::Scaner(char* path)
{
    loadFile(path);
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
    do {
        this->text[i++] = static_cast<char>(inputStream.get());
    }while (!inputStream.eof());
    this->text[i-1] = '$';
    inputStream.close();
}

int Scaner::doScan(LEX)
{
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
        LEX lex;
        unsigned int i=0;
        lex[i++] = text[pointer++];
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
        }

    }
}

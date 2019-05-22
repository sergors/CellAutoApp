#ifndef SCANER_H
#define SCANER_H

#include "interpreter/defs.h"

//class for identify lexems
class Scaner
{
private:
    TEXT text;
    unsigned int pointer;
    int column;
    int row;
public:
    Scaner(char*);
    Scaner(const char*);
    ~Scaner();
    void setPointer(unsigned int);
    unsigned int getPointer();
    void setRow(int);
    int getRow();
    void setColumn(int);
    int getColumn();

    void loadFile(char*);
    void loadFromGUI();
    int doScan(LEX);
    void showError(char*, char*);
};

#endif // SCANER_H

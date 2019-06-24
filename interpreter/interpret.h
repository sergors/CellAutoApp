#ifndef INTERPRET_H
#define INTERPRET_H

#include "parser/parser.h"
#include "string"

class Interpret
{
private:
    bool start; //глобальный флаг
    Parser *parser;
    bool** globalArea;
public:
    Interpret(Parser *parser);
    ~Interpret();
    void setGlobalStart(bool f);
    void runInterpret();
    void runOnlyParse();
    void saveCellAutoState();
    void printError(string error);
    bool** getGlobalArea();
};

#endif // INTERPRET_H

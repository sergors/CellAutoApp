#ifndef PARSER_H
#define PARSER_H

#include <interpreter/scaner/scaner.h>
#include <interpreter/semantik/SemTree.h>
#include <interpreter/semantik/Semantik.h>

class Parser {
private:
    Scaner *scaner;
    Semantik *sem;
public:
    Parser(Scaner *s);
    int readNextLex(LEX lex);
    void S();
    void element();
    void classArray();
    void cellAuto();
    void data();
    void arrayList();
    void type();
    void expression();
    void add();
    void mul();
    void elExpression();
    void arrayInit();
    void variable();
    void actualParameters();
    void array();
    void name();
    void nameInner();
    void constant();
};
#endif

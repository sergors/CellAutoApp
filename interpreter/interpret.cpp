#include "interpret.h"
#include "qdebug.h"

Interpret::Interpret(Parser *parser) {
    this->parser = parser;
    this->globalArea = new bool*[100];
    for (int i = 0; i < 100; i++){
        globalArea[i] = new bool[100];
    }

}

Interpret::~Interpret() {
    for (int i = 0; i < 100; i++){
       delete [] globalArea[i];
    }
    delete [] globalArea;
}

bool** Interpret::getGlobalArea() {
    return this->globalArea;
}

void Interpret::setGlobalStart(bool f) {
    this->start = f;
}

void Interpret::saveCellAutoState() {

}

void Interpret::runInterpret() {
    this->parser->S();
}
void Interpret::runOnlyParse() {
    this->parser->S();
}
void Interpret::printError(string error) {
    string desc = "Unexpected error: ";
    qDebug() << desc.c_str() << error.c_str();
}

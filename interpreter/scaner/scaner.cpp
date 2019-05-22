#include "scaner.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <QDebug>

static LEX keywords[MAXKEY] = {
    "var", "int", "bool", "neig", "ClassArray", "CellAuto", "System", "true", "false", "const", "new"
};
static int indexkeywords[MAXKEY] = {
  t_var, t_int, t_bool, t_neig, t_class_array, t_cell_auto, t_system, t_true, t_false, t_const, t_new
};

Scaner::Scaner(char* path) {
    loadFile(path);
    pointer = 0;
    row = 1;
    column = 1;
}
Scaner::Scaner(const char* text) {
    strcpy(this->text, text);
    pointer = 0;
    row = 1;
    column = 1;
}
Scaner::~Scaner(){}

void Scaner::setPointer(unsigned int pointer) {
    this->pointer = pointer;
}
unsigned int Scaner::getPointer() {
    return this->pointer;
}
void Scaner::setRow(int row) {
    this->row = row;
}
int Scaner::getRow() {
    return this->row;
}
void Scaner::setColumn(int column) {
    this->column = column;
}
int Scaner::getColumn() {
    return this->column;
}

void Scaner::loadFile(char* path) {
    ifstream inputStream(path);
    unsigned int i = 0;
    if(inputStream) {
        do {
            this->text[i++] = static_cast<char>(inputStream.get());
        }while (!inputStream.eof());
        this->text[i-1] = '$';
        inputStream.close();
    } else {
        string fileName(path);
        throw runtime_error("error open file with name = " + fileName);
    }
}

void Scaner::showError(char* err, char* a) {
    if(a[0]=='\0')
        printf("Error(%d:%d): %s %s\n",this->column,this->column,err,a);
    else
        printf("Error(%d:%d): %s. Read: %s\n",this->column,this->column,err,a);
}

int Scaner::doScan(LEX lex) {
    for(int i=0; i< MAXLEX;i++)
        lex[i] = '\0';
    unsigned int i=0;
    start:
    //skip spec symbols
    while(text[pointer] == ' ' ||
          text[pointer] == '\n' ||
          text[pointer] == '\t') {
        if(text[pointer] == '\t' || text[pointer] == ' ')
            this->column++;
        if(text[pointer] == '\n')
            this->row++;
        pointer++;
    }
    //skip one row comment
    if(text[pointer] == '/' && text[pointer+1] == '/') {
        pointer+=2;
        column+=2;
        while(text[pointer]!='\n' && text[pointer] != '\0') {
            column++;
            pointer++;
        }
        if(text[pointer] == '\n') {
            column = 1;
            row++;
            pointer++;
        }
        goto start;
    }
    //identificator or keyword
    if((text[pointer] >= 'a' && text[pointer] <='z') ||
       (text[pointer] >= 'A' && text[pointer] <='Z') ||
            text[pointer] == '_') {
        lex[i++] = this->text[pointer++];
        column++;

        while((text[pointer] >= 'a' && text[pointer] <= 'z') ||
              (text[pointer] >= 'A' && text[pointer] <= 'Z') ||
              (text[pointer] >= '0' && text[pointer] <= '9') ||
              text[pointer] == '_') {
            if(i<MAXLEX - 1) {
                lex[i++] = text[pointer++];
                column++;
            } else {
                while((text[pointer] >= 'a' && text[pointer] <= 'z') ||
                      (text[pointer] >= 'A' && text[pointer] <= 'Z') ||
                      (text[pointer] >= '0' && text[pointer] <= '9') ||
                      text[pointer] == '_') {
                    lex[i++] = text[pointer++];
                    column++;
                }
                showError("Превышена максимально допустимая длина идентификатора", lex);
                return t_error;
            }
        }
        for(int i = 0; i < MAXKEY; i++) {
            if(strcmp(keywords[i], lex) == 0)
                return indexkeywords[i];
        }
        return t_id;
    //digit constants without sign???
    } else if (text[pointer] >= '1' && text[pointer] <= '9') {
        int capacity = 0;
        lex[capacity++] = text[pointer++]; column++;
        while(isdigit(text[pointer])) {
            if(capacity < MAX_INT) {
                lex[capacity++] = text[pointer++]; column++;
            } else {
                showError("max length constant", lex);
                while(text[pointer] >= '0' && text[pointer] <= '9') {
                    pointer++;
                    column++;
                }
                return t_error;
            }
        }
        if(text[pointer] == '.') { //double?
            lex[capacity++] = text[pointer++]; column++;
            while(isdigit(text[pointer])) {
                lex[capacity++] = text[pointer++]; column++;
                if(capacity > MAX_DOUBLE - 1) {
                    showError("превышена максимально допустимая длина константы", lex);
                    return t_error;
                }
            }
            return t_double;
        }
        if(capacity <= 9) {
            return t_int;
        } else {
            return t_long;
        }
     //digit constant 0 or 0.
    } else if(text[pointer] == '0') {
        lex[i++] = text[pointer++]; column++;
        if(isalpha(text[pointer]) || isdigit(text[pointer])) {
            lex[i++] = text[pointer++]; column++;
            showError("Ошибка в объявлении константы", lex);
            return t_error;
        } else if (text[pointer] == '.') {
            lex[i++] = text[pointer++]; column++;
            while(isdigit(text[pointer])) {
                lex[i++] = text[pointer]++; column++;
                if(i > MAX_DOUBLE - 1) {
                    showError("превышена максимально допустимая длина константы", lex);
                    return t_error;
                }
            }
            return t_double;
        } else {
            return t_int;
        }
    } else if(text[pointer] == '{') {
        lex[i++] = text[pointer++]; column++;
        return t_op_brace;
    } else if(text[pointer] == '}') {
        lex[i++] = text[pointer++]; column++;
        return t_cl_brace;
    } else if(text[pointer] == '(') {
        lex[i++] = text[pointer++]; column++;
        return t_op_round_bkt;
    } else if(text[pointer] == ')') {
        lex[i++] = text[pointer++]; column++;
        return t_cl_round_bkt;
    } else if(text[pointer] == '[') {
        lex[i++] = text[pointer++]; column++;
        return t_op_square_bkt;
    } else if(text[pointer] == ']') {
        lex[i++] = text[pointer++]; column++;;
        return t_cl_square_bkt;
    } else if(text[pointer] == ';') {
        lex[i++] = text[pointer++]; column++;
        return  t_semicolon;
    } else if(text[pointer] == '=') {
        lex[i++] = text[pointer++]; column++;
        return t_assignment;
    } else if(text[pointer] == '#') {
        lex[i++] = text[pointer++]; column++;
        return t_scharp;
    } else if(text[pointer] == ':') {
        lex[i++] = text[pointer++]; column++;
        return t_colon;
    } else if(text[pointer] == '.') {
        lex[i++] = text[pointer++]; column++;
        return t_dot;
    } else if(text[pointer] == ',') {
        lex[i++] = text[pointer++]; column++;;
        return t_comma;
    } else if(text[pointer] == '-' && text[pointer + 1] == '>') {
        lex[i++] = text[pointer++]; column++;
        lex[i++] = text[pointer++]; column++;
        return t_lambda;
    } else if(text[pointer] == '*') {
        lex[i++] = text[pointer++]; column++;
        return t_star;
    } else if(text[pointer] == '$') { //end of program text
        lex[0] = text[pointer];
        return t_end;
    }
    return t_undefined;
}

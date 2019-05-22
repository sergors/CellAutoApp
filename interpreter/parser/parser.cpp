#include "parser.h"

Parser::Parser(Scaner *s) {
    this->scaner = s;
    this->tree = new SemTree();
    this->tree->setCursor(tree);
}

void Parser::S() {
    LEX lex;
    int t;
    t = readNextLex(lex);
    while(t == t_scharp || t == t_cell_auto || t == t_int ||
          t == t_double || t == t_long || t == t_class_array ||
          t == t_bool || t == t_id) {
        element();
        t = readNextLex(lex);
    }
    t = this->scaner->doScan(lex);
    if(t != t_end) {
        this->scaner->showError("Expected end program!",lex);
    }
}

void Parser::element() {
    LEX lex;
    int t;
    t = readNextLex(lex);
    if(t == t_cell_auto) {
        cellAuto();
    } else if (t == t_class_array) {
        classArray();
    } else if(t == t_const) {
        this->scaner->doScan(lex);
        t = readNextLex(lex);
        if(t != t_int && t != t_double && t != t_long && t != t_bool && t != t_id) {
            this->scaner->showError("Expected lex for DNN diag(int, double, long, bool)", lex);
        }
        data();
        t = readNextLex(lex);
        if(t != t_semicolon) {
            this->scaner->showError("Expected lex in ELM diag(;) after DNN", lex);
        }
    } else if(t == t_int || t == t_double || t == t_long || t == t_bool || t == t_id) {
        data();
        t = readNextLex(lex);
        if(t != t_semicolon) {
            this->scaner->showError("Expected lex in ELM diag(;) after DNN", lex);
        }
    } else {
        this->scaner->showError("Unexpected lex in ELM diag",lex);
    }
}
void Parser::cellAuto() {

}
void Parser::classArray() {

}
void Parser::data() {
    LEX lex;
    int t;
    t = this->scaner->doScan(lex); // object type
    t = readNextLex(lex);
    if(t != t_op_square_bkt || t != t_id) {
        this->scaner->showError("DNN: Expected [ or identifier", lex);
    }
    if(t == t_op_square_bkt) {
        t = this->scaner->doScan(lex);              //  [
        t = readNextLex(lex);
        if(t != t_cl_square_bkt) {
            expression();                           //read izm
            t = readNextLex(lex);
            while(t == t_comma) {
                expression();                       //read izm
            }
        }
        t = this->scaner->doScan(lex);              //  ]
        t = readNextLex(lex);
        while(t == t_id) {
            t = this->scaner->doScan(lex);          //identifier
            t = readNextLex(lex);
            if(t == t_assignment) {
                t = this->scaner->doScan(lex);      // =
                t = readNextLex(lex);
                if(t == t_new) {
                    t = this->scaner->doScan(lex);  // new
                    type();
                    t = this->scaner->doScan(lex);
                    if(t != t_op_square_bkt) {
                        this->scaner->showError("DNN: Expected [", lex);
                    }
                    expression();
                    t = this->scaner->doScan(lex);
                    if(t != t_cl_square_bkt) {
                        this->scaner->showError("DNN: Expected ]", lex);
                    }
                } else if(t == t_op_brace) {
                    t = this->scaner->doScan(lex);    // {
                    arrayInit();
                }
            }
        }
    } else {
        variable();
        t = readNextLex(lex);
        while(t == t_comma) {
            variable();
        }
    }
}
void Parser::arrayList() {
    LEX lex;
    int t;
    t = readNextLex(lex);
    while(t == t_id) {
        t = this->scaner->doScan(lex);                     // identifier
        t = readNextLex(lex);
        if(t == t_assignment) {
            t = this->scaner->doScan(lex);                 // =
            t = readNextLex(lex);
            if(t == t_new) {
                type();
            }
        }
    }
}

void Parser::type() {
    LEX lex;
    int t;
    t = this->scaner->doScan(lex);
    if(t != t_int && t != t_long && t != t_double && t != t_bool && t != t_id) {
        this->scaner->showError("TYP.Expected any type", lex);
    }
}

void Parser::expression() {

}

//INM
void Parser::arrayInit() {
    LEX lex;
    int t;
    expression();
    t = readNextLex(lex);
    while(t == t_comma) {
        t = this->scaner->doScan(lex);              // ,
        expression();
        t = readNextLex(lex);
    }
}

void Parser::variable() {
    LEX lex;
    int t;
    t = this->scaner->doScan(lex);
    if(t != t_id) {
        this->scaner->showError("VAR: Expected identifier", lex);
    }
    t = readNextLex(lex);
    if(t == t_assignment) {
        t = this->scaner->doScan(lex);            // =
        t = readNextLex(lex);
        if(t == t_new) {
            t = this->scaner->doScan(lex);        // new
            type();
            t = this->scaner->doScan(lex);        //  (
            if(t != t_op_round_bkt) {
                this->scaner->showError("VAR: Expected (", lex);
            }
            actualParameters();
            t = this->scaner->doScan(lex);
            if(t != t_cl_round_bkt) {
                this->scaner->showError("VAR: Expected )", lex);
            }
        }
    }
}
void Parser::actualParameters() {
    LEX lex;
    int t;
    expression();
    t = readNextLex(lex);
    while(t == t_comma) {
        t = this->scaner->doScan(lex);        // ,
        expression();
        t = readNextLex(lex);
    }
}
int Parser::readNextLex(LEX lex) {
    int t, column, row;
    unsigned int pointer;
    pointer = this->scaner->getPointer();
    column = this->scaner->getColumn();
    row = this->scaner->getRow();
    t = this->scaner->doScan(lex);
    this->scaner->setPointer(pointer);
    this->scaner->setColumn(column);
    this->scaner->setRow(row);
    return t;
}

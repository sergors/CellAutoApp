#include "parser.h"

Parser::Parser(Scaner *s) {
    this->scaner = s;
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
        cellAuto();                                        //  CellAuto
    } else if (t == t_class_array) {
        classArray();                                      // classArray
    } else if(t == t_const) {
        this->scaner->doScan(lex);                         //  "const"
    }
    data();                                                //  DNN (data)
    t = this->scaner->doScan(lex);
    if(t != t_semicolon) {
        this->scaner->showError("Expected lex in ELM diag(;) after DNN", lex);
    }
}
void Parser::cellAuto() {

}
void Parser::classArray() {
    LEX lex;
    int t;
    t = this->scaner->doScan(lex);               //classArray
    if(t != t_class_array) {
        this->scaner->showError("CLA: Expected classArray", lex);
    }
    t = this->scaner->doScan(lex);               // identifier
    if(t != t_id) {
        this->scaner->showError("CLA: Expected class array identifier", lex);
    }
    t = this->scaner->doScan(lex);              // <
    if(t != t_less) {
        this->scaner->showError("CLA: Expected < after identifier", lex);
    }
    expression();
    t = this->scaner->doScan(lex);
    if(t != t_comma) {
        this->scaner->showError("CLA: Expected , after <EXP", lex);
    }
    expression();
    t = this->scaner->doScan(lex);
    if(t != t_more) {
        this->scaner->showError("CLA: Expected > after <EXP,EXP", lex);
    }
    t = this->scaner->doScan(lex);
    if(t != t_op_brace) {
        this->scaner->showError("CLA: Expected { after classArray declaring", lex);
    }
    //class array body
    t = readNextLex(lex);
    if(t != t_neig || t != t_int || t != t_long ||
       t != t_double || t != t_bool || t != t_cl_brace) {
        this->scaner->showError("CLA: Expected } or class array body elements (neig, field)", lex);
    }
    while(t == t_neig || t == t_int || t == t_long ||
          t == t_double || t == t_bool) {
        if(t == t_neig) {
            t = this->scaner->doScan(lex);               // neig
            t = this->scaner->doScan(lex);               // identifier
            if(t != t_id) {
                this->scaner->showError("CLA: Expected neig identifier", lex);
            }
            t = this->scaner->doScan(lex);               //  =
            if(t != t_assignment) {
                this->scaner->showError("CLA: Expected = after neig identifier", lex);
            }
            // neig body
            t = this->scaner->doScan(lex);            // #
            if(t != t_scharp) {
                this->scaner->showError("CLA: Expected # in neig body", lex);
            }
            t = this->scaner->doScan(lex);            // [
            if(t != t_op_brace) {
                this->scaner->showError("CLA: Expected [ after #", lex);
            }
            t = this->scaner->doScan(lex);            // integer const
            if(t != t_int) {
                this->scaner->showError("CLA: Expected int const in neig body after #[", lex);
            }
            t = readNextLex(lex);
            while(t == t_comma) {
                t = this->scaner->doScan(lex);        //  ,
                t = this->scaner->doScan(lex);
                if(t != t_int) {
                    this->scaner->showError("CLA: Expected integer const in neig body after ,", lex);
                }
                t = readNextLex(lex);
            }
            //end neig body
            t = this->scaner->doScan(lex);
            if(t != t_cl_brace) {
                this->scaner->showError("CLA: Expected } after neig body", lex);
            }                  // }
        } else {
            // field
            t = this->scaner->doScan(lex);                  // type
            t = this->scaner->doScan(lex);                  // [ or
            if(t == t_op_square_bkt) {
                //IZM
                expression();                               //read izm
                t = readNextLex(lex);
                while(t == t_comma) {
                    t = this->scaner->doScan(lex);          //   ,
                    expression();                           //read izm
                    t = readNextLex(lex);
                }
                t = this->scaner->doScan(lex);              //  ]
                if(t != t_cl_square_bkt) {
                    this->scaner->showError("CLA(FLD): Expected ] after TYP [IZM", lex);
                }
            }
            t = this->scaner->doScan(lex);
            if(t!= t_id) {
                this->scaner->showError("CLA(FLD): Expected identifier", lex);
            }
            t = readNextLex(lex);
            while (t == t_comma) {
                t = this->scaner->doScan(lex);              // ,

            }
        }
        t = readNextLex(lex);
    }
    t = this->scaner->doScan(lex);                         // }
}

void Parser::data() {
    LEX lex;
    int t;
    type();                                          // type (int, bool, etc...)
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
                t = this->scaner->doScan(lex);      //   ,
                expression();                       //read izm
                t = readNextLex(lex);
            }
        }
        t = this->scaner->doScan(lex);              //  ]
        if(t != t_cl_square_bkt) {
            this->scaner->showError("DNN: Expected ] after TYP [IZM", lex);
        }
        array();
        t = readNextLex(lex);
        while(t == t_comma) {
            array();
        }
    } else {
        variable();
        t = readNextLex(lex);
        while(t == t_comma) {
            variable();
        }
    }
}

void Parser::array() {
    LEX lex;
    int t;
    t = this->scaner->doScan(lex);          //identifier
    if(t != t_id) {
        this->scaner->showError("MSV: Expected identifier", lex);
    }
    t = readNextLex(lex);
    if(t == t_assignment) {
        t = this->scaner->doScan(lex);      // =
        t = readNextLex(lex);
        if(t == t_new) {
            t = this->scaner->doScan(lex);  // new
            type();
            t = this->scaner->doScan(lex);
            if(t != t_op_square_bkt) {
                this->scaner->showError("MSV: Expected [", lex);
            }
            expression();
            t = this->scaner->doScan(lex);
            if(t != t_cl_square_bkt) {
                this->scaner->showError("MSV: Expected ]", lex);
            }
        } else if(t == t_op_brace) {
            t = this->scaner->doScan(lex);                  // {
            expression();
            t = readNextLex(lex);
            while(t == t_comma) {
                t = this->scaner->doScan(lex);              // ,
                expression();
                t = readNextLex(lex);
            }
            t = this->scaner->doScan(lex);
            if(t != t_cl_brace) {
                this->scaner->showError("MSV: Expected }", lex);
            }
        } else {
            expression();
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
    LEX lex;
    int t;
    t = readNextLex(lex);
    if(t == t_plus || t == t_star) {
        t = this->scaner->doScan(lex);           // + or -
    }
    add();
    t = readNextLex(lex);
    while(t == t_more || t == t_more_equal || t == t_less || t == t_less_equal ||
          t == t_equal || t == t_not_equal || t == t_and || t == t_or) {
        add();
        t = readNextLex(lex);
    }
}

void Parser::add() {
    LEX lex;
    int t;
    mul();
    t = readNextLex(lex);
    while(t == t_plus || t == t_minus) {
        mul();
        t = readNextLex(lex);
    }
}

void Parser::mul() {
    LEX lex;
    int t;
    elExpression();
    t = readNextLex(lex);
    while(t == t_star || t == t_div) {
        elExpression();
        t = readNextLex(lex);
    }
}

void Parser::elExpression() {
    LEX lex;
    int t;
    t = readNextLex(lex);
    if(t == t_int_const || t == t_long_const || t == t_double_const || t_bool_const) {
        constant();
    } else if(t == t_op_round_bkt) {
        t = this->scaner->doScan(lex);           // (
        expression();
        t = this->scaner->doScan(lex);          //   )
        if(t != t_cl_round_bkt) {
            this->scaner->showError("EEX: Expected ) after (EXP", lex);
        }
    } else {
        name();
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

void Parser::name() {
    LEX lex;
    int t;
    nameInner();
    t = readNextLex(lex);
    if(t == t_op_round_bkt) {
        actualParameters();
        t = readNextLex(lex);
        if(t == t_colon) {
            //Cell Auto start
            t = this->scaner->doScan(lex);     // :
            expression();
            t = this->scaner->doScan(lex);     // ,
            if(t != t_comma) {
                this->scaner->showError("NME(SCA): Expected , after :EXP", lex);
            }
            expression();
        }
        t = this->scaner->doScan(lex);
        if(t != t_cl_round_bkt) {
            this->scaner->showError("NME: Expected ) after SCA", lex);
        }
    }
}
void Parser::nameInner() {
    LEX lex;
    int t;
    t = this->scaner->doScan(lex);              // identifier
    if(t != t_id) {
        this->scaner->showError("NM2: Expected identifier", lex);
    }
    t = readNextLex(lex);
    if(t == t_op_square_bkt) {
        t = this->scaner->doScan(lex);          // [
        expression();
        t = readNextLex(lex);
        while(t == t_comma) {
            expression();
            t = readNextLex(lex);
        }
        t = this->scaner->doScan(lex);          // ]
        if(t != t_cl_square_bkt) {
            this->scaner->showError("NM2: Expected ] after [EXP", lex);
        }
    }
    t = readNextLex(lex);
    while(t == t_dot) {
        t = this->scaner->doScan(lex);          // .
        t = this->scaner->doScan(lex);          // identifier or #
        if(t != t_id || t != t_scharp) {
            this->scaner->showError("NM2: Expected identifier or # after .", lex);
        }
        t = readNextLex(lex);
        if(t == t_op_square_bkt) {
            t = this->scaner->doScan(lex);          // [
            expression();
            t = readNextLex(lex);
            while(t == t_comma) {
                expression();
                t = readNextLex(lex);
            }
            t = this->scaner->doScan(lex);          // ]
            if(t != t_cl_square_bkt) {
                this->scaner->showError("NM2: Expected ] after [EXP", lex);
            }
        }
        t = readNextLex(lex);
    }
}

void Parser::constant() {
    LEX lex;
    int t;
    t = this->scaner->doScan(lex);
    if(t == t_int_const) {

    } else if(t == t_long_const) {

    } else if (t == t_double_const) {

    } else if(t == t_bool_const) {

    } else {
        this->scaner->showError("CNT: Expected any constant!", lex);
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

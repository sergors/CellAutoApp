#ifndef SEMANTIK_H
#define SEMANTIK_H

#include <interpreter/scaner/scaner.h>
#include "ElmSemTree.h"
#include "StackTree.h"
#include "SemTree.h"

class Semantik
{
public:
    Scaner *scan;
    SemTree *tree;
    StackTree *stackTree;
    DATA_TYPE save_type;
    ElmSemTree *save_utype;

    int save_izm;
    bool save_const;
    bool save_param;
    bool save_external;
    bool save_var;

    ElmSemTree *fun;

    bool fspike;
    bool varadd;
    bool fusa;

    Semantik(Scaner *scanIn);
    ~Semantik();
    void clear();
    void clearSaveFlags();
    ElmSemTree* getSaveElmOfTree();
    void saveIncIzm();
    void saveConstChange(bool f);
    void saveExternalChange(bool f);
    void impAccessChange(bool f);
    void saveParamChange(bool f);
    void saveVarChange(bool f);
    void spikeChange(bool f);
    void opFunOn();
    bool checkValueOfCellBaseP();
    bool checkValueOfCellBaseE();
    bool checkPointerOfCellBase();
    bool checkPointerOfCellRightP();
    bool checkPointerOfCellRightE();
    bool saveType(int type, LEX lex);
    bool addVar(LEX lex);
    bool addFun();
    bool addCellAuto();
    bool addContextSub();
    bool addSystemSub();
    bool addSub();
    bool addClassArray();
    void addNul();
    bool checkVar(LEX lex, OBJECT_TYPE obj, DATA_TYPE type);
    ElmSemTree* findIdent(LEX lex);
    bool checkObjForPrisv(ElmSemTree *obj);
    void createSystemObjects();
    bool createObjectCA();
    bool createSystemFunctions();


};

#endif // SEMANTIK_H

#ifndef SEMTREE_H
#define SEMTREE_H

#include <interpreter/scaner/scaner.h>
#include "ElmSemTree.h"

enum DATA_TYPE {
    TYPE_EMPTY = 1,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_CL_ARRAY,
    TYPE_CELL_AUTO
};
enum OBJECT_TYPE {
    OBJECT_VAR = 1,
    OBJECT_ARRAY,
    OBJECT_FUN,
    OBJECT_CLASS_ARRAY,
    OBJECT_SYSTEM,
    OBJECT_CELL_AUTO,
    OBJECT_SYSTEM_SUB,
    OBJECT_CONTEXT_SUB,
    OBJECT_SUB,
    OBJECT_NULL
};

class SemTree {
    ElmSemTree *n;
    SemTree *up, *left, *right;
public:
    static SemTree *cursor;
    SemTree();
    void setCursor(SemTree *t);
};

#endif // SEMTREE_H

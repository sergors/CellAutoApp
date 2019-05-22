#ifndef SEMTREE_H
#define SEMTREE_H

#include <interpreter/scaner/scaner.h>

enum DATA_TYPE {
    TYPE_EMPTY = 1,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_CL_ARRAY,
    TYPE_CELL_AUTO
};

struct Node {
    LEX id;
    DATA_TYPE dataType;
};

class SemTree {
    Node *n;
    SemTree *up, *left, *right;
public:
    static SemTree *cursor;
    SemTree();
    void setCursor(SemTree *t);
};

#endif // SEMTREE_H

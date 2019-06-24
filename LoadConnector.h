#ifndef LOADCONNECTOR_H
#define LOADCONNECTOR_H

#include <interpreter/interpret.h>

enum PROG_STATE {
    COMPILE = 1,
    START,
    STOP,
    PAUSE
};

class LoadConnector
{
private:
    Interpret *intrp;
    PROG_STATE progState;

public:
    LoadConnector(Interpret *intrp);
    void setProgState(PROG_STATE);
    PROG_STATE getProgState();
    bool** getGlobalArea();
};

#endif // LOADCONNECTOR_H

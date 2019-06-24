#include "LoadConnector.h"

LoadConnector::LoadConnector(Interpret *intrp)
{
    this->intrp = intrp;
}

PROG_STATE LoadConnector::getProgState() {
    return this->progState;
}

void LoadConnector::setProgState(PROG_STATE prgState) {
    this->progState = prgState;
    if(this->progState == COMPILE) {
        intrp->setGlobalStart(false);
        intrp->runOnlyParse();
    } else if(this->progState == START) {
        intrp->setGlobalStart(true);
        intrp->runInterpret();
    } else if(this->progState == STOP) {
        intrp->setGlobalStart(false);
    } else if(this->progState == PAUSE) {
        intrp->setGlobalStart(false);
        intrp->saveCellAutoState();
    } else {
        intrp->printError("Undefinded PROG_STATE" + prgState);
    }
}

bool** LoadConnector::getGlobalArea() {
    return intrp->getGlobalArea();
}

#pragma once

#include <string>
#include "automatonState.h"

class AutomatonTransition {
    private:
        AutomatonState* inititalState;
        AutomatonState* resultState;
        char symbolRead;
    public:
        AutomatonTransition();
        AutomatonTransition(AutomatonState* init, AutomatonState* result, char symbol);
        AutomatonState* getInitState();
        AutomatonState* getResultState();
        char getSymbolRead();
        void setInitState(AutomatonState* i){inititalState = i;}
        void setResultState(AutomatonState* r){resultState = r;}
        void setSymbol(char s){symbolRead = s;}
        
};


#pragma once

#include "symbol.h"

class VariableElement : public Symbol {
    
    private:
    
        char value;

    public:

        VariableElement();

        VariableElement(char value);
};
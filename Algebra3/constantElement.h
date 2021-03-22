#pragma once

#include "symbol.h"

class ConstantElement : public Symbol {

    private:

        int value;

    public:

        ConstantElement();

        ConstantElement(int value);
        
};
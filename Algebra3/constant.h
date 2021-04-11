#pragma once

#include "symbol.h"

class Constant : public Symbol {

    private:

        int value;

    public:

        Constant();

        Constant(int value);

        void appendChild(unique_ptr<Symbol>& child) override;

        void appendChild(Symbol* child) override;

        unique_ptr<Symbol> copy() override;

        string toString() override;
        
};
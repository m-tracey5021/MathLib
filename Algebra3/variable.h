#pragma once

#include "symbol.h"

class Variable : public Symbol {
    
    private:
    
        char value;

    public:

        Variable();

        Variable(char value);

        void appendChild(unique_ptr<Symbol>& child) override;

        void appendChild(Symbol* child) override;

        unique_ptr<Symbol> copy() override;

        string toString() override;
};
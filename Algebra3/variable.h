#pragma once

#include "symbol.h"

class Variable : public Symbol {
    
    private:
    
        char value;

    public:

        Variable();

        Variable(char value);

        void appendChild(unique_ptr<Symbol>& child) override;

        unique_ptr<Symbol>& getNthChild(int n) override;

        vector<unique_ptr<Symbol>>& getAllChildren() override;

        unique_ptr<Symbol> copy() override;

        string toString() override;
};
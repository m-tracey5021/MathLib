#pragma once

#include "symbol.h"
#include "expressionComponents.h"

class Variable : public Symbol {
    
    private:
    
        char value;

    public:

        Variable();

        Variable(char value);

        Variable(bool sign, char value);

        // Variable(unique_ptr<AuxOp>& auxOp, char value);

        // Variable(bool sign, unique_ptr<AuxOp>& auxOp, char value);

        

        int getValue() override;

        void appendChild(unique_ptr<Symbol>& child) override;

        unique_ptr<Symbol>& getNthChild(int n) override;

        vector<unique_ptr<Symbol>>& getAllChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren(int start, int end) override;

        unique_ptr<Symbol>& expandExponent() override;

        unique_ptr<Symbol>& expandAsExponent(unique_ptr<Symbol>& base) override;

        unique_ptr<Symbol> copy() override;

        string toString() override;

        string toString(int depth, int offset) override;
};
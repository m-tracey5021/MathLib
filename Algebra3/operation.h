#pragma once

#include "symbol.h"
#include "expressionComponents.h"

// struct Scope {
//     vector<pair<char, int>> ops;
//     int start;
//     int end;
// };

class Operation : public Symbol {

    protected:

        // Scope scope;

        vector<unique_ptr<Symbol>> operands;

    public:

        Operation();

        Operation(char op);

        Operation(char op, bool sign);

        Operation(char op, bool sign, vector<unique_ptr<Symbol>>& operands);

        ~Operation();

        // Operation(char op, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        // Operation(char op, bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        

        

        void appendChild(unique_ptr<Symbol>& child) override;

        // void appendChild(unique_ptr<Operation>& child);

        unique_ptr<Symbol>& getNthChild(int n) override;

        vector<unique_ptr<Symbol>>& getAllChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren(int start, int end) override;

        int getValue() override;

        unique_ptr<Symbol>& expandExponent() override;

        unique_ptr<Symbol>& expandAsExponent(unique_ptr<Symbol>& base) override;

        unique_ptr<Symbol> copy() override;

        string toString() override;

        string toString(int depth, int offset) override;

};
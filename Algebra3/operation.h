#pragma once

#include "symbol.h"

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

        Operation(char op, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        Operation(char op, bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        void appendChild(unique_ptr<Symbol>& child) override;

        void appendChild(Symbol* child) override;

        virtual unique_ptr<Symbol> copy() = 0;

        virtual string toString() = 0;

};
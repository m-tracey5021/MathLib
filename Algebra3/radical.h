// #pragma once

// #include "auxOp.h"
// #include "symbol.h"

// class Radical : public AuxOp {

//     private:

//     public:

//         Radical();

//         Radical(unique_ptr<Symbol>& root);

//         unique_ptr<AuxOp> copy() override;

//         string toString(string target) override;
        
// };

#pragma once

#include "operation.h"

class Radical : public Operation {

    private:

    public:

        Radical();

        Radical(bool sign);

        Radical(bool sign, vector<unique_ptr<Symbol>>& operands);

        // Radical(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        // Radical(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        int getValue() override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
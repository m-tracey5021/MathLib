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

        Radical(bool sign, vector<unique_ptr<Symbol>>& children);

        Radical(bool sign, shared_ptr<Expression>& parentExpression);

        Radical(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        int getValue() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
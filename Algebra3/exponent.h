// #pragma once

// #include "auxOp.h"
// #include "symbol.h"

// class Exponent : public AuxOp {

//     private:



//     public:

//         Exponent();

//         Exponent(unique_ptr<Symbol>& root);

//         unique_ptr<AuxOp> copy() override;

//         string toString(string target) override;

// };

#pragma once

#include "operation.h"

class Exponent : public Operation {

    private:


    public:

        Exponent();

        Exponent(bool sign);

        Exponent(bool sign, vector<unique_ptr<Symbol>>& children);

        Exponent(bool sign, shared_ptr<Expression>& parentExpression);

        Exponent(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        int getValue() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
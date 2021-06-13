// #pragma once

// #include "auxOp.h"
// #include "symbol.h"

// class Exponent : public AuxOp {

//     private:



//     public:

//         Exponent();

//         Exponent(shared_ptr<Symbol>& root);

//         shared_ptr<AuxOp> copy() override;

//         string toString(string target) override;

// };

#pragma once

#include "operation.h"

class Exponent : public Operation {

    private:


    public:

        Exponent();

        Exponent(bool sign);

        Exponent(bool sign, vector<shared_ptr<Symbol>>& children);

        Exponent(bool sign, shared_ptr<Expression>& parentExpression);

        Exponent(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        void accept(Visitor* visitor) override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        // void appendChild(shared_ptr<Symbol>& child) override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        shared_ptr<Symbol> copy() override;

        shared_ptr<Symbol> sanitise() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
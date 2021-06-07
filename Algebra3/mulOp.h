#pragma once

#include "operation.h"

class MulOp : public Operation {

    private:

    public:

        MulOp();

        MulOp(bool sign);

        MulOp(bool sign, vector<unique_ptr<Symbol>>& children);

        MulOp(bool sign, shared_ptr<Expression>& parentExpression);

        MulOp(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        unique_ptr<Symbol> extractCoeff();

        int getValue() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void replaceChild(unique_ptr<MulOp>& child, int n) override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
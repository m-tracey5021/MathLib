#pragma once

#include "operation.h"

class DivOp : public Operation {

    private:

    public:

        DivOp();

        DivOp(bool sign);

        DivOp(bool sign, vector<unique_ptr<Symbol>>& children);

        DivOp(bool sign, shared_ptr<Expression>& parentExpression);

        DivOp(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        int getValue() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
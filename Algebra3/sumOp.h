#pragma once

#include "operation.h"

class SumOp : public Operation {

    private:

    public:

        SumOp();

        SumOp(bool sign);

        SumOp(bool sign, vector<unique_ptr<Symbol>>& children);

        SumOp(bool sign, shared_ptr<Expression>& parentExpression);

        SumOp(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        // SumOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        // SumOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        int getValue() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void replaceChild(unique_ptr<SumOp>& child, int n) override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
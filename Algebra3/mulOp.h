#pragma once

#include "operation.h"

class MulOp : public Operation {

    private:

    public:

        MulOp();

        MulOp(bool sign);

        MulOp(bool sign, vector<shared_ptr<Symbol>>& children);

        MulOp(bool sign, shared_ptr<Expression>& parentExpression);

        MulOp(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        unique_ptr<Symbol> extractCoeff();

        void accept(Visitor* visitor) override;

        int getValue() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void appendChild(shared_ptr<Symbol>& child) override;

        void appendToParent(SumOp* parent) override;
        void appendToParent(MulOp* parent) override;
        void appendToParent(DivOp* parent) override;
        void appendToParent(Exponent* parent) override;
        void appendToParent(Radical* parent) override;
        void appendToParent(Constant* parent) override;
        void appendToParent(Variable* parent) override;

        void replaceChild(shared_ptr<MulOp>& child, int n) override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        shared_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
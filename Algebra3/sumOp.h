#pragma once

#include "operation.h"

class SumOp : public Operation {

    private:

    public:

        SumOp();

        SumOp(bool sign);

        SumOp(bool sign, vector<shared_ptr<Symbol>>& children);

        SumOp(bool sign, shared_ptr<Expression>& parentExpression);

        SumOp(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        // SumOp(shared_ptr<AuxOp>& auxOp, vector<shared_ptr<Symbol>>& operands);

        // SumOp(bool sign, shared_ptr<AuxOp>& auxOp, vector<shared_ptr<Symbol>>& operands);

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

        // void appendChild(shared_ptr<SumOp> child) override;
        // void appendChild(shared_ptr<MulOp> child) override;
        // void appendChild(shared_ptr<DivOp> child) override;
        // void appendChild(shared_ptr<Constant> child) override;
        // void appendChild(shared_ptr<Variable> child) override;

        void replaceChild(shared_ptr<SumOp>& child, int n) override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        shared_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
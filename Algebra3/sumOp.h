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

        void accept(Visitor* visitor) override;


        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        // void appendChild(shared_ptr<Symbol>& child) override;

        void evaluateConstants() override;

        void evaluateSingleConstant(optional<int>& result, int& index, int& total, bool& totalSign) override;    

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        shared_ptr<Symbol> copy() override;

        shared_ptr<Symbol> sanitise() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
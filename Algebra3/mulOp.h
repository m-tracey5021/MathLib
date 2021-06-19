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

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isEqual(Symbol* other) override;
        

        // void appendChild(shared_ptr<Symbol>& child) override;

        void evaluateConstants() override;

        void evaluateSingleConstant(optional<int>& result, int& index, int& total, bool& totalSign);    

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        shared_ptr<Symbol> copy() override;

        shared_ptr<Symbol> sanitise() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
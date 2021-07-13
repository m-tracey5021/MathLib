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

        bool isEqual(Symbol* other) override;

        bool isLikeTerm(Symbol* other) override;

        void evaluateConstants() override;

        void evaluateSingleConstant(optional<int>& result, int& index, int& total, bool& totalSign);    

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        void sumLikeTerms() override;

        shared_ptr<Symbol> copy() override;

        shared_ptr<Symbol> sanitise() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
#pragma once

#include "operation.h"

class DivOp : public Operation {

    private:

    public:

        DivOp();

        DivOp(bool sign);

        DivOp(bool sign, vector<shared_ptr<Symbol>>& children);

        DivOp(bool sign, shared_ptr<Expression>& parentExpression);

        DivOp(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        void accept(Visitor* visitor) override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isEqual(Symbol* other) override;
        
        bool isLikeTerm(Symbol* other) override;

        // void appendChild(shared_ptr<Symbol>& child) override;

        void evaluateConstants() override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        void sumLikeTerms() override;

        shared_ptr<Symbol> copy() override;

        shared_ptr<Symbol> sanitise() override;

        string toString(bool hasParent) override;

        // string toString(int& depth, int offset) override;

};
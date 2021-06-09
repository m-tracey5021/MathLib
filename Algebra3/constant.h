#pragma once

#include "atom.h"

class Constant : public Atom {

    private:

        int value;

    public:

        Constant();

        Constant(int value);

        Constant(bool sign, int value);

        Constant(bool sign, int value, shared_ptr<Expression>& parentExpression);

        // Constant(shared_ptr<AuxOp>& auxOp, int value);

        // Constant(bool sign, shared_ptr<AuxOp>& auxOp, int value);

        void accept(Visitor* visitor) override;

        int getValue() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void appendToParent(SumOp* parent) override;
        void appendToParent(MulOp* parent) override;
        void appendToParent(DivOp* parent) override;
        void appendToParent(Exponent* parent) override;
        void appendToParent(Radical* parent) override;
        void appendToParent(Constant* parent) override;
        void appendToParent(Variable* parent) override;

        // void appendChild(shared_ptr<Symbol>& child) override;

        // void appendChildren(vector<shared_ptr<Symbol>>& children) override;

        // void appendChildren(vector<shared_ptr<Symbol>>& children, int n) override;

        // void replaceChild(shared_ptr<Symbol>& child, int n) override;

        // void removeChild(shared_ptr<Symbol>& child) override;

        // void removeChild(int n) override;

        // shared_ptr<Symbol>& getChild(int n) override;        

        // vector<shared_ptr<Symbol>>& getAllChildren() override;

        // vector<shared_ptr<Symbol>> duplicateChildren() override;

        // vector<shared_ptr<Symbol>> duplicateChildren(int start, int end) override;

        // void expandExponent(Symbol* parent, Symbol* grandparent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        shared_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        string toString(int depth, int offset) override;
        
};
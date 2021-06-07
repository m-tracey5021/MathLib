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

        // Constant(unique_ptr<AuxOp>& auxOp, int value);

        // Constant(bool sign, unique_ptr<AuxOp>& auxOp, int value);

        

        int getValue() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        // void appendChild(unique_ptr<Symbol>& child) override;

        // void appendChildren(vector<unique_ptr<Symbol>>& children) override;

        // void appendChildren(vector<unique_ptr<Symbol>>& children, int n) override;

        // void replaceChild(unique_ptr<Symbol>& child, int n) override;

        // void removeChild(unique_ptr<Symbol>& child) override;

        // void removeChild(int n) override;

        // unique_ptr<Symbol>& getChild(int n) override;        

        // vector<unique_ptr<Symbol>>& getAllChildren() override;

        // vector<unique_ptr<Symbol>> duplicateChildren() override;

        // vector<unique_ptr<Symbol>> duplicateChildren(int start, int end) override;

        // void expandExponent(Symbol* parent, Symbol* grandparent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        string toString(int depth, int offset) override;
        
};
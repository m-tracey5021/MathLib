#pragma once

#include "symbol.h"

class SumOp;
class MulOp;

class Atom : public Symbol {
    
    protected:
    


    public:

        Atom();

        Atom(char symbol);

        Atom(char symbol, bool sign);

        Atom(char symbol, bool sign, shared_ptr<Expression>& parentExpression);

        // Atom(unique_ptr<AuxOp>& auxOp, char value);

        // Atom(bool sign, unique_ptr<AuxOp>& auxOp, char value);

        

        int getValue() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        // bool isParentTo(Symbol* symbol) override;

        // unique_ptr<Symbol>& searchParent(Symbol* symbol, unique_ptr<Symbol>& parent) override;

        void setChildren(vector<unique_ptr<Symbol>>& children) override;

        void appendChild(unique_ptr<Symbol>& child) override;
        // void appendChild(unique_ptr<SumOp> child) override;
        // void appendChild(unique_ptr<MulOp> child) override;
        // void appendChild(unique_ptr<DivOp> child) override;
        // void appendChild(unique_ptr<Constant> child) override;
        // void appendChild(unique_ptr<Variable> child) override;

        void appendChildren(vector<unique_ptr<Symbol>>& children) override;

        void appendChildren(vector<unique_ptr<Symbol>>& children, int n) override;

        void replaceChild(unique_ptr<Symbol>& child, int n) override;
        void replaceChild(unique_ptr<SumOp>& child, int n) override;
        void replaceChild(unique_ptr<MulOp>& child, int n) override;

        void removeChild(unique_ptr<Symbol>& child) override;

        void removeChild(int n) override;

        

        unique_ptr<Symbol>& getChild(int n) override;

        vector<unique_ptr<Symbol>>& getChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren(int start, int end) override;

        void expandExponent(Symbol* parent) override;

        void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        unique_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        string toString(int depth, int offset) override;
};
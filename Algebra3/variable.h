#pragma once

#include "atom.h"

class Variable : public Atom {
    
    private:
    
        char value;

    public:

        Variable();

        Variable(char value);

        Variable(bool sign, char value);

        Variable(bool sign, char value, shared_ptr<Expression>& parentExpression);

        // Variable(shared_ptr<AuxOp>& auxOp, char value);

        // Variable(bool sign, shared_ptr<AuxOp>& auxOp, char value);

        void accept(Visitor* visitor) override;

        optional<int> getValue() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

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
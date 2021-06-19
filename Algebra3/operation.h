#pragma once

#include "symbol.h"
#include "Visitors/appendToMulOp.h"

// struct Scope {
//     vector<pair<char, int>> ops;
//     int start;
//     int end;
// };

class SumOp;
class MulOp;

class Operation : public Symbol {

    protected:

        // Scope scope;

        // vector<shared_ptr<Symbol>> operands;

    public:

        Operation();

        Operation(char op);

        Operation(char op, bool sign);

        Operation(char op, bool sign, vector<shared_ptr<Symbol>>& children);

        Operation(char symbol, bool sign, shared_ptr<Expression>& parentExpression);

        Operation(char symbol, bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        ~Operation();


        optional<int> getValue() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        void setChildren(vector<shared_ptr<Symbol>>& children) override;

        void appendChild(shared_ptr<Symbol>& child) override;

        void appendChildren(vector<shared_ptr<Symbol>>& children) override;

        void appendChildren(vector<shared_ptr<Symbol>>& children, int n) override;

        void replaceChild(shared_ptr<Symbol>& child, int n) override;

        void removeChild(shared_ptr<Symbol>& child) override;

        void removeChild(int n) override;

        

        // shared_ptr<Symbol>& getChild(int n) override;

        // vector<shared_ptr<Symbol>>& getChildren() override;

        vector<shared_ptr<Symbol>> duplicateChildren() override;

        vector<shared_ptr<Symbol>> duplicateChildren(int start, int end) override;

        void evaluateConstants() override;

        // void expandExponent(Symbol* parent) override;

        // void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) override;

        shared_ptr<Symbol> copy() override;

        string toString(bool hasParent) override;

        string toString(int depth, int offset) override;

};
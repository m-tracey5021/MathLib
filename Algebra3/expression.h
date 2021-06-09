#pragma once

#include "symbol.h"
#include "operation.h"

class Expression {

    private:

        shared_ptr<Symbol> root;

        unique_ptr<Symbol> rootNull;

        // vector<shared_ptr<Symbol>> context;

    public:

        Expression();

        Expression(shared_ptr<Symbol>& root);

        shared_ptr<Symbol>& getRoot();

        unique_ptr<Symbol>& getRootNull();

        shared_ptr<Symbol>& getNode(Symbol* target);

        // shared_ptr<Symbol>& getParent(Symbol* target);

        // shared_ptr<Symbol>& getParent(Symbol* target, shared_ptr<Symbol>& parent, shared_ptr<Symbol>& child);

        void setRoot(shared_ptr<Symbol>& root);

        void replaceNode(Symbol* target, shared_ptr<Symbol>& symbol);

        // void addNode(shared_ptr<Symbol>& symbol);

        // void replaceNode(shared_ptr<Symbol>& symbol, Symbol* target);

        // void removeNode(shared_ptr<Symbol>& symbol);

        void expandExponents();

        string toString();

        string toString(int offset);
};

void link(shared_ptr<Expression>& expression, shared_ptr<Symbol>& root);


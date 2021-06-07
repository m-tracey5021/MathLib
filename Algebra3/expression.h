#pragma once

#include "symbol.h"
#include "operation.h"

class Expression {

    private:

        unique_ptr<Symbol> root;

        unique_ptr<Symbol> rootNull;

        // vector<unique_ptr<Symbol>> context;

    public:

        Expression();

        Expression(unique_ptr<Symbol>& root);

        unique_ptr<Symbol>& getRoot();

        unique_ptr<Symbol>& getRootNull();

        unique_ptr<Symbol>& getNode(Symbol* target);

        unique_ptr<Symbol>& getParent(Symbol* target);

        unique_ptr<Symbol>& getParent(Symbol* target, unique_ptr<Symbol>& parent, unique_ptr<Symbol>& child);

        void setRoot(unique_ptr<Symbol>& root);

        void replaceNode(Symbol* target, unique_ptr<Symbol>& symbol);

        // void addNode(unique_ptr<Symbol>& symbol);

        // void replaceNode(unique_ptr<Symbol>& symbol, Symbol* target);

        // void removeNode(unique_ptr<Symbol>& symbol);

        void expandExponents();

        string toString();

        string toString(int offset);
};

void link(shared_ptr<Expression>& expression, unique_ptr<Symbol>& root);


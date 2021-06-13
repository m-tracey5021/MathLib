#pragma once

#include "symbol.h"
#include "operation.h"

class Expression {

    private:

        shared_ptr<Symbol> root;

        shared_ptr<Symbol> rootNull;

        // vector<shared_ptr<Symbol>> context;

    public:

        Expression();

        Expression(shared_ptr<Symbol>& root);

        shared_ptr<Symbol>& getRoot();

        shared_ptr<Symbol>& getRootNull();

        shared_ptr<Symbol> getNode(vector<int> path);

        shared_ptr<Symbol> getNode(Symbol* target);

        optional<shared_ptr<Symbol>> getNode(Symbol* target, shared_ptr<Symbol> current);

        void setRoot(shared_ptr<Symbol>& root);

        void appendNode(shared_ptr<Symbol>& parent, shared_ptr<Symbol>& child);

        void removeNode(Symbol* target);

        void insertNode(Symbol* target, shared_ptr<Symbol>& replacement);

        void replaceNode(Symbol* target, shared_ptr<Symbol>& replacement);


        void expandExponents();

        string toString();

        string toString(int offset);
};

void link(shared_ptr<Expression>& expression, shared_ptr<Symbol>& root);


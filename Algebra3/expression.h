#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <optional>

#include "symbolContainer.h"

using std::string;
using std::vector;
using std::map;

using std::shared_ptr;
using std::make_shared;

using std::optional;
using std::nullopt;

class Expression {

    private:

        vector<shared_ptr<SymbolContainerBase>> tree;

        map<int, int> parentMap; // key is node, value is parent

        map<int, vector<int>> childMap; // key is node, value is children

    public:

        Expression();

        Expression(vector<shared_ptr<SymbolContainerBase>> tree);

        int getNode(shared_ptr<SymbolContainerBase>& node);

        int getParent(shared_ptr<SymbolContainerBase>& node);

        vector<int> getChildren(shared_ptr<SymbolContainerBase>& node);

        void addNode(shared_ptr<SymbolContainerBase>& root);

        void addNode(shared_ptr<SymbolContainerBase>& parent, shared_ptr<SymbolContainerBase>& child);

        void addNodes(shared_ptr<SymbolContainerBase>& parent, vector<shared_ptr<SymbolContainerBase>> children);

        // void applyToTree(shared_ptr<SymbolContainerBase>& operation);

        string toString();



};


class ExpressionBuilder {

    private:

        Expression expression;

    public:

        shared_ptr<SymbolContainerBase> buildSymbol(bool sign, char symbol);

        void build();

        void plus(int constant);

        void minus(int constant);

        void times(int constant);

        void divide(int constant);

        void raise(int constant);

        void floor(int constant);

        void plus(char variable);

        void minus(char variable);

        void times(char variable);

        void divide(char variable);

        void raise(char variable);

        void floor(char variable);

        void plus(Expression expression);

        void minus(Expression expression);

        void times(Expression expression);

        void divide(Expression expression);

        void raise(Expression expression);

        void floor(Expression expression);

        Expression get();

};



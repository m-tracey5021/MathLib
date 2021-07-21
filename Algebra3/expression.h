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

        shared_ptr<SymbolContainerBase> buildSymbol(bool sign, char symbol, optional<int> value);

        string toString();



};




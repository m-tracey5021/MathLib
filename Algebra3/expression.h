#pragma once

#include <vector>
#include <memory>

#include "symbolContainer.h"

using std::vector;
using std::shared_ptr;

class Expression {

    private:

        vector<shared_ptr<SymbolContainerBase>> tree;

    public:

        Expression();

        Expression(vector<shared_ptr<SymbolContainerBase>> tree);

};




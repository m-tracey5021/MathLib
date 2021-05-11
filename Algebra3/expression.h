#pragma once

#include "symbol.h"
#include "operation.h"

class Expression {

    private:

        unique_ptr<Symbol> root;

    public:

        Expression();

        Expression(unique_ptr<Symbol>& symbol);

        unique_ptr<Symbol> getRoot();

        void setRoot(unique_ptr<Symbol>& symbol);

        void setRoot(unique_ptr<Operation>& symbol);

        void setRoot(Symbol* symbol);

        string toString();
};
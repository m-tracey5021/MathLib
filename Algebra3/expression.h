#pragma once

#include "symbol.h"

class Expression {

    private:

        unique_ptr<Symbol> rootSymbol;

    public:

        Expression();

        Expression(unique_ptr<Symbol>& rootSymbol);
};
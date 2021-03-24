#pragma once

#include "symbol.h"

class Expressionn {

    private:

        unique_ptr<Symbol> rootSymbol;

    public:

        Expressionn();

        Expressionn(unique_ptr<Symbol>& rootSymbol);
};
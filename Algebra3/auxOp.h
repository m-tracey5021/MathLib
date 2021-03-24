#pragma once

#include <memory>

using std::unique_ptr;
using std::move;
using std::make_unique;

class Symbol;

class AuxOp {

    protected:

        unique_ptr<Symbol> rootSymbol;

    public:

        AuxOp();

        AuxOp(unique_ptr<Symbol>& rootSymbol);

        ~AuxOp();

};

#pragma once

#include "auxOp.h"
#include "symbol.h"

class Function : public AuxOp {
    
    private:

        unique_ptr<Symbol> definition;

    public:

        Function();

        Function(unique_ptr<Symbol>& rootSymbol);

        Function(unique_ptr<Symbol>& rootSymbol, unique_ptr<Symbol>& definition);

        unique_ptr<AuxOp> copy() override;

        string toString() override;
};
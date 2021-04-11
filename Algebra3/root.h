#pragma once

#include "auxOp.h"
#include "symbol.h"

class Root : public AuxOp {

    private:

    public:

        Root();

        Root(unique_ptr<Symbol>& rootSymbol);

        unique_ptr<AuxOp> copy() override;

        string toString() override;
        
};
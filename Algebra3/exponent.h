#pragma once

#include "auxOp.h"
#include "symbol.h"

class Exponent : public AuxOp {

    private:



    public:

        Exponent();

        Exponent(unique_ptr<Symbol>& rootSymbol);

        unique_ptr<AuxOp> copy() override;

        string toString() override;

};
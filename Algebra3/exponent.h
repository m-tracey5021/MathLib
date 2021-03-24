#pragma once

#include "auxOp.h"

class Exponent : public AuxOp {

    private:



    public:

        Exponent();

        Exponent(unique_ptr<Symbol>& rootSymbol);

};
#pragma once

#include "auxOp.h"

class Root : public AuxOp {

    private:

    public:

        Root();

        Root(unique_ptr<Symbol>& rootSymbol);
        
};
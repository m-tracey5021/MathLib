#pragma once

#include "auxOp.h"
#include "symbol.h"

class Radical : public AuxOp {

    private:

    public:

        Radical();

        Radical(unique_ptr<Symbol>& root);

        unique_ptr<AuxOp> copy() override;

        string toString(string target) override;
        
};
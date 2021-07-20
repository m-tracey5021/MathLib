#pragma once

#include "symbol.h"

class Radical : public Symbol {

    public:

        Radical();

        Expression add(SumOp& other) override;
        Expression add(MulOp& other) override;
        Expression add(DivOp& other) override;
        Expression add(Exponent& other) override;
        Expression add(Radical& other) override;
        Expression add(Variable& other) override;
        Expression add(Constant& other) override;

        string toString() override;
    

};
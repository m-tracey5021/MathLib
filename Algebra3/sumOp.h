#pragma once

#include "operation.h"

class SumOp : public Operation {

    private:

    public:

        SumOp();

        SumOp(bool sign);

        SumOp(bool sign, vector<unique_ptr<Symbol>>& operands);

        SumOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        SumOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        unique_ptr<Symbol> copy() override;

        string toString() override;

};
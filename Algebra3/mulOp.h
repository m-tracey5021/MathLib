#pragma once

#include "operation.h"

class MulOp : public Operation {

    private:

    public:

        MulOp();

        MulOp(bool sign);

        MulOp(bool sign, vector<unique_ptr<Symbol>>& operands);

        MulOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        MulOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        unique_ptr<Symbol> copy() override;

        string toString() override;

};
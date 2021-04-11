#pragma once

#include "operation.h"

class DivOp : public Operation {

    private:

    public:

        DivOp();

        DivOp(bool sign);

        DivOp(bool sign, vector<unique_ptr<Symbol>>& operands);

        DivOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        DivOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        unique_ptr<Symbol> copy() override;

        string toString() override;

};
#pragma once

#include "operation.h"
#include "expressionComponents.h"

class SumOp : public Operation {

    private:

    public:

        SumOp();

        SumOp(bool sign);

        SumOp(bool sign, vector<unique_ptr<Symbol>>& operands);

        // SumOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        // SumOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        int getValue() override;

        unique_ptr<Symbol>& expandExponent() override;

        unique_ptr<Symbol>& expandAsExponent(unique_ptr<Symbol>& base) override;

        unique_ptr<Symbol> copy() override;

        string toString() override;

        // string toString(int& depth, int offset) override;

};
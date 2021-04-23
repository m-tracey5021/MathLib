// #pragma once

// #include "auxOp.h"
// #include "symbol.h"

// class Exponent : public AuxOp {

//     private:



//     public:

//         Exponent();

//         Exponent(unique_ptr<Symbol>& root);

//         unique_ptr<AuxOp> copy() override;

//         string toString(string target) override;

// };

#pragma once

#include "operation.h"

class Exponent : public Operation {

    private:

    public:

        Exponent();

        Exponent(bool sign);

        Exponent(bool sign, vector<unique_ptr<Symbol>>& operands);

        Exponent(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        Exponent(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands);

        unique_ptr<Symbol> copy() override;

        string toString(bool includeAuxilliaries) override;

};
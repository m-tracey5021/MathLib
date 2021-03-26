#include "sumOp.h"

SumOp::SumOp(): Operation('+'){}

SumOp::SumOp(bool sign): Operation('+', sign){}

SumOp::SumOp(bool sign, vector<unique_ptr<Symbol>> operands): Operation('+', sign, operands){}

SumOp::SumOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>> operands): Operation('+', true, auxOp, operands){}

SumOp::SumOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>> operands): Operation('+', sign, auxOp, operands){}

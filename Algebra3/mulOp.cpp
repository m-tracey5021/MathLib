#include "mulOp.h"

MulOp::MulOp(): Operation('*'){}

MulOp::MulOp(bool sign, vector<unique_ptr<Symbol>> operands): Operation('*', sign, operands){}

MulOp::MulOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>> operands): Operation('*', true, auxOp, operands){}

MulOp::MulOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>> operands): Operation('*', sign, auxOp, operands){}
#include "divOp.h"

DivOp::DivOp(): Operation('/'){}

DivOp::DivOp(bool sign): Operation('/'), sign(sign){}

DivOp::DivOp(bool sign, vector<unique_ptr<Symbol>> operands): Operation('/', sign, operands){}

DivOp::DivOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>> operands): Operation('/', true, auxOp, operands){}

DivOp::DivOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>> operands): Operation('/', sign, auxOp, operands){}
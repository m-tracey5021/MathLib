#include "mulOp.h"
#include "expression.h"
#include "expressionComponents.h"

MulOp::MulOp(): Symbol('*', nullopt){}

Expression MulOp::add(SumOp& other){}

Expression MulOp::add(MulOp& other){}

Expression MulOp::add(DivOp& other){}

Expression MulOp::add(Exponent& other){}

Expression MulOp::add(Radical& other){}

Expression MulOp::add(Variable& other){}

Expression MulOp::add(Constant& other){}

string MulOp::toString(){ string result = ""; return result + symbol; }
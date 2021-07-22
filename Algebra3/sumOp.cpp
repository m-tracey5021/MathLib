#include "sumOp.h"
#include "expression.h"
#include "expressionComponents.h"

SumOp::SumOp(): Symbol('+', nullopt){}

Expression SumOp::add(SumOp& other){}

Expression SumOp::add(MulOp& other){}

Expression SumOp::add(DivOp& other){}

Expression SumOp::add(Exponent& other){}

Expression SumOp::add(Radical& other){}

Expression SumOp::add(Variable& other){}

Expression SumOp::add(Constant& other){}

string SumOp::toString(){ string result = ""; return result + symbol; }
#include "divOp.h"
#include "expression.h"
#include "expressionComponents.h"

DivOp::DivOp(): Symbol('/', nullopt){}

Expression DivOp::add(SumOp& other){}

Expression DivOp::add(MulOp& other){}

Expression DivOp::add(DivOp& other){}

Expression DivOp::add(Exponent& other){}

Expression DivOp::add(Radical& other){}

Expression DivOp::add(Variable& other){}

Expression DivOp::add(Constant& other){}

string DivOp::toString(){ string result = ""; return result + symbol; }
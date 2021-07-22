#include "constant.h"
#include "expression.h"
#include "expressionComponents.h"

Constant::Constant(): Symbol(){}

Constant::Constant(int constant): Symbol(constant, constant), constant(constant){}

Expression Constant::add(SumOp& other){}

Expression Constant::add(MulOp& other){}

Expression Constant::add(DivOp& other){}

Expression Constant::add(Exponent& other){}

Expression Constant::add(Radical& other){}

Expression Constant::add(Variable& other){}

Expression Constant::add(Constant& other){}

string Constant::toString(){ string result = ""; return result + symbol; }
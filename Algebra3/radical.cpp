
#include "radical.h"
#include "expression.h"
#include "expressionComponents.h"

Radical::Radical(): Symbol('v', nullopt){}

Expression Radical::add(SumOp& other){}

Expression Radical::add(MulOp& other){}

Expression Radical::add(DivOp& other){}

Expression Radical::add(Exponent& other){}

Expression Radical::add(Radical& other){}

Expression Radical::add(Variable& other){}

Expression Radical::add(Constant& other){}

string Radical::toString(){ string result = ""; return result + symbol; }
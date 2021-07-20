
#include "exponent.h"
#include "expressionComponents.h"

Exponent::Exponent(): Symbol('^', nullopt){}

Expression Exponent::add(SumOp& other){}

Expression Exponent::add(MulOp& other){}

Expression Exponent::add(DivOp& other){}

Expression Exponent::add(Exponent& other){}

Expression Exponent::add(Radical& other){}

Expression Exponent::add(Variable& other){}

Expression Exponent::add(Constant& other){}

string Exponent::toString(){ string result = ""; return result + symbol; }
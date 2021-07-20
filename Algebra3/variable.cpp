#include "variable.h"
#include "expressionComponents.h"

Variable::Variable(): Symbol(){}

Variable::Variable(char variable): Symbol(variable, nullopt), variable(variable){}

Expression Variable::add(SumOp& other){}

Expression Variable::add(MulOp& other){}

Expression Variable::add(DivOp& other){}

Expression Variable::add(Exponent& other){}

Expression Variable::add(Radical& other){}

Expression Variable::add(Variable& other){}

Expression Variable::add(Constant& other){}

string Variable::toString(){ string result = ""; return result + symbol; }
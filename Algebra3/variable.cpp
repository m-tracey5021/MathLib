#include "variable.h"

Variable::Variable(): Symbol(){}

Variable::Variable(char value): Symbol(value), value(value){}

void Variable::appendChild(unique_ptr<Symbol>& child){}

void Variable::appendChild(Symbol* child){}

unique_ptr<Symbol> Variable::copy(){
    unique_ptr<Symbol> copy = make_unique<Variable>(value);
    return copy;
}

string Variable::toString(){
    string ret = "";
    return ret + value;
}
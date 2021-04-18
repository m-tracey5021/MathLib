#include "constant.h"

Constant::Constant(): Symbol(){}

Constant::Constant(int value): Symbol(value), value(value){}

void Constant::appendChild(unique_ptr<Symbol>& child){}

unique_ptr<Symbol>& Constant::getNthChild(int n){
    unique_ptr<Symbol> null;
    return null;
}

vector<unique_ptr<Symbol>>& Constant::getAllChildren(){}

unique_ptr<Symbol> Constant::copy(){

    unique_ptr<Symbol> copy = make_unique<Constant>(value);
    return copy;
}

string Constant::toString(){
    return std::to_string(value);
}
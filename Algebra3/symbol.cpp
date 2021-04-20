#include "symbol.h"

Symbol::Symbol(){}

Symbol::Symbol(char symbol): symbol(symbol), sign(true){}

Symbol::Symbol(char symbol, bool sign): symbol(symbol), sign(sign){}

Symbol::Symbol(char symbol, unique_ptr<AuxOp>& auxOp): symbol(symbol), sign(true), auxOp(move(auxOp)){}

Symbol::Symbol(char symbol, bool sign, unique_ptr<AuxOp>& auxOp): symbol(symbol), sign(sign), auxOp(move(auxOp)){}

Symbol::~Symbol() = default;

void Symbol::setParent(shared_ptr<Symbol>& parent){
    this->parent = parent;
}

void Symbol::appendAuxillary(unique_ptr<AuxOp>& auxOp){
    this->auxOp = move(auxOp);
}

void Symbol::appendChild(unique_ptr<Symbol>& child){}

shared_ptr<Symbol>& Symbol::getParent(){
    return parent;
}

unique_ptr<AuxOp>& Symbol::getAuxillary(){
    return auxOp;
}

unique_ptr<Symbol>& Symbol::getNthChild(int n){}

vector<unique_ptr<Symbol>>& Symbol::getAllChildren(){}

unique_ptr<Symbol> Symbol::copy(){}

string Symbol::toString(bool includeAuxilliaries){return "";}
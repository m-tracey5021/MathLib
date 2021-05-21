#include "symbol.h"

Symbol::Symbol(){}

Symbol::Symbol(char symbol): symbol(symbol), sign(true), isTarget(false), isExponent(false), isRadical(false){}

Symbol::Symbol(char symbol, bool sign): symbol(symbol), sign(sign), isTarget(false), isExponent(false), isRadical(false){}

// Symbol::Symbol(char symbol, unique_ptr<AuxOp>& auxOp): symbol(symbol), sign(true), auxOp(move(auxOp)){}

// Symbol::Symbol(char symbol, bool sign, unique_ptr<AuxOp>& auxOp): symbol(symbol), sign(sign), auxOp(move(auxOp)){}

Symbol::~Symbol() = default;

char Symbol::getSymbol(){return symbol;}

bool Symbol::getSign(){return sign;}

bool Symbol::getIsTarget(){return isTarget;}

bool Symbol::getIsExponent(){return isExponent;}

bool Symbol::getIsRadical(){return isRadical;}

shared_ptr<Symbol>& Symbol::getParent(){
    return parent;
}

void Symbol::setSymbol(char symbol){
    this->symbol = symbol;
}

void Symbol::setSign(bool sign){
    this->sign = sign;
}

void Symbol::setAsTarget(bool isTarget){
    this->isTarget = isTarget;
}

void Symbol::setAsExponent(bool isExponent){
    this->isExponent = isExponent;
}

void Symbol::setAsRadical(bool isRadical){
    this->isRadical = isRadical;
}

void Symbol::setParent(shared_ptr<Symbol>& parent){
    this->parent = parent;
}

// void Symbol::appendAuxillary(unique_ptr<AuxOp>& auxOp){
//     this->auxOp = move(auxOp);
// }





int Symbol::getValue(){}



// unique_ptr<AuxOp>& Symbol::getAuxillary(){
//     return auxOp;
// }

void Symbol::appendChild(unique_ptr<Symbol>& child){}

unique_ptr<Symbol>& Symbol::getNthChild(int n){}

vector<unique_ptr<Symbol>>& Symbol::getAllChildren(){}

vector<unique_ptr<Symbol>> Symbol::duplicateChildren(){}

vector<unique_ptr<Symbol>> Symbol::duplicateChildren(int start, int end){}

unique_ptr<Symbol>& Symbol::expandExponent(){}

unique_ptr<Symbol>& Symbol::expandAsExponent(unique_ptr<Symbol>& base){}

unique_ptr<Symbol> Symbol::copy(){}

string Symbol::toString(){return "";}

string Symbol::toString(int depth, int offset){return "";}
#include "symbol.h"
#include "expressionComponents.h"

Symbol::Symbol(): index(-1){}

Symbol::Symbol(char symbol): symbol(symbol), sign(true), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign): symbol(symbol), sign(sign), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign, vector<shared_ptr<Symbol>>& children): symbol(symbol), sign(sign), children(move(children)), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign, shared_ptr<Expression>& parentExpression): symbol(symbol), sign(sign), parentExpression(parentExpression), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): symbol(symbol), sign(sign), children(move(children)), parentExpression(parentExpression), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::~Symbol() = default;

char Symbol::getSymbol(){return symbol;}

bool Symbol::getSign(){return sign;}

bool Symbol::getIsTarget(){return isTarget;}

bool Symbol::getIsExponent(){return isExponent;}

bool Symbol::getIsRadical(){return isRadical;}

int Symbol::getIndex(){return index;}

// shared_ptr<Symbol>& Symbol::getParent(){
//     return parentExpression->getParent(this);
// }

shared_ptr<Symbol>& Symbol::getParent(){return parent;}

vector<shared_ptr<Symbol>>& Symbol::getChildren(){return children;}

shared_ptr<Expression>& Symbol::getParentExpression(){return parentExpression;}

void Symbol::setSymbol(char symbol){
    this->symbol = symbol;
}

void Symbol::setSign(bool sign){
    this->sign = sign;
}

void Symbol::setIsTarget(bool isTarget){
    this->isTarget = isTarget;
}

void Symbol::setIsExponent(bool isExponent){
    this->isExponent = isExponent;
}

void Symbol::setIsRadical(bool isRadical){
    this->isRadical = isRadical;
}

void Symbol::setIndex(int index){
    this->index = index;
}

void Symbol::setParentExpression(shared_ptr<Expression>& parentExpression){
    this->parentExpression = parentExpression;
}

void Symbol::testVariant(variant<shared_ptr<SumOp>, shared_ptr<MulOp>, shared_ptr<DivOp>> symbols){
    
}




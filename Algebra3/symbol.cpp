#include "symbol.h"
#include "expressionComponents.h"

Symbol::Symbol(): index(-1){}

Symbol::Symbol(char symbol): symbol(symbol), sign(true), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign): symbol(symbol), sign(sign), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign, vector<shared_ptr<Symbol>>& children): symbol(symbol), sign(sign), children(move(children)), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign, shared_ptr<Expression>& parentExpression): symbol(symbol), sign(sign), path({-1}), parentExpression(parentExpression), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(char symbol, bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): symbol(symbol), sign(sign), path({-1}), children(move(children)), parentExpression(parentExpression), isTarget(false), isExponent(false), isRadical(false), index(-1){}

Symbol::Symbol(const Symbol& other){
    symbol = other.symbol;
    sign = other.sign;
    isTarget = other.isTarget;
    isExponent = other.isExponent;
    isRadical = other.isRadical;

}

Symbol& Symbol::operator=(const Symbol& other){

}

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

vector<int> Symbol::getPath(){return path;}

int Symbol::getPathValue(){return path[path.size() - 1];}

shared_ptr<Symbol> Symbol::getParent(){return parent;}

shared_ptr<Symbol> Symbol::getWrapped(){return parentExpression->getNode(path);}

vector<shared_ptr<Symbol>>& Symbol::getChildren(){return children;}

shared_ptr<Expression> Symbol::getParentExpression(){return parentExpression;}

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

void Symbol::setPath(vector<int> path){
    this->path = path;
}

void Symbol::setPathValue(int value){
    path[path.size() - 1] = value;
}

void Symbol::setParent(shared_ptr<Symbol> parent){
    this->parent = parent;
}

void Symbol::setParentExpression(shared_ptr<Expression> parentExpression){
    this->parentExpression = parentExpression;
}


// void append(Symbol& parent, shared_ptr<Symbol>& child){
//     child->setIndex(parent.getChildren().size());
//     child->setParentExpression(parent.getParentExpression());
//     parent.getChildren().push_back(move(child));
// }

// void appendEach(Symbol& parent, shared_ptr<Symbol>& child){
//     vector<shared_ptr<Symbol>>& children = child->getChildren();
//     for (int i = 0; i < children.size(); i ++){
//         children[i]->setIndex(i);
//         children[i]->setParentExpression(parent.getParentExpression());
//         parent.getChildren().push_back(move(children[i]));
//     }
// }




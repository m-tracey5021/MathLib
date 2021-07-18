
#include "exponent.h"
#include "expressionComponents.h"
#include "Visitors/equalTo.h"

Exponent::Exponent(): Operation('^'){}

Exponent::Exponent(bool sign): Operation('^', sign){}

Exponent::Exponent(bool sign, vector<shared_ptr<Symbol>>& children): Operation('^', sign, children){}

Exponent::Exponent(bool sign, shared_ptr<Expression>& parentExpression): Operation('^', sign, parentExpression){}

Exponent::Exponent(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('^', sign, children, parentExpression){}

void Exponent::accept(Visitor* visitor){
    visitor->Visit(this);
}

bool Exponent::isAtomicExponent(){
    if (children[1]->isAtomicExponent()){
        return true;
    }else{
        return false;
    }
}

bool Exponent::isAtomicNumerator(){return true;}

bool Exponent::isEqual(Symbol* other){
    shared_ptr<EqualToExponent> equal = make_shared<EqualToExponent>(*this);
    other->accept(equal.get());
    return equal->isEqual;
}

bool Exponent::isLikeTerm(Symbol* other){return false;}


void Exponent::evaluateConstants(){
    for (int i = 0; i < children.size(); i ++){
        children[i]->evaluateConstants();
    }
}

void Exponent::expandExponent(Symbol* parent){
    if (!children[1]->isAtomicExponent()){
        children[1]->expandAsExponent(*children[0], this, parent);
    }
    return;
}


void Exponent::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    if (!children[1]->isAtomicExponent()){
        children[1]->expandAsExponent(*children[0], this, parent);
    }
    parent->expandExponent(grandparent);
}

void Exponent::sumLikeTerms(){
    for (shared_ptr<Symbol> child : children){
        child->sumLikeTerms();
    }
}

shared_ptr<Symbol> Exponent::evaluate(){}

shared_ptr<Symbol> Exponent::sum(Symbol& other){

}

shared_ptr<Symbol> Exponent::multiply(Symbol& other){
    
}

shared_ptr<Symbol> Exponent::divide(Symbol& other){
    
}

shared_ptr<Symbol> Exponent::copy(){

    shared_ptr<Symbol> copy = make_shared<Exponent>(sign);
    vector<shared_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        shared_ptr<Symbol> copied = children[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    copy->setIndex(index);
    return copy;
}

shared_ptr<Symbol> Exponent::sanitise(){
    
}

string Exponent::toString(bool hasParent){
    string ret = "";
    for (int i = 0; i < children.size(); i ++){
        if (i < children.size() - 1){
            ret += children[i]->toString(true) + '^';
        }else{
            ret += children[i]->toString(true);
        }
    }
    if (!sign){
        ret = "-(" + ret + ')';
    }else{
    
    }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }else if(isTarget){
        ret = '(' + ret + ')';
    }
    return ret;
}
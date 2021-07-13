
#include "radical.h"
#include "expressionComponents.h"
#include "Visitors/equalTo.h"

Radical::Radical(): Operation('v'){}

Radical::Radical(bool sign): Operation('v', sign){}

Radical::Radical(bool sign, vector<shared_ptr<Symbol>>& children): Operation('v', sign, children){}

Radical::Radical(bool sign, shared_ptr<Expression>& parentExpression): Operation('v', sign, parentExpression){}

Radical::Radical(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('v', sign, children, parentExpression){}

void Radical::accept(Visitor* visitor){
    visitor->Visit(this);
}

bool Radical::isAtomicExponent(){return true;}

bool Radical::isAtomicNumerator(){return true;}

bool Radical::isEqual(Symbol* other){
    shared_ptr<EqualToRadical> equal = make_shared<EqualToRadical>(*this);
    other->accept(equal.get());
    return equal->isEqual;
}

bool Radical::isLikeTerm(Symbol* other){return false;}

// void Radical::appendChild(shared_ptr<Symbol>& child){
//     child->setIndex(children.size());
//     child->setParentExpression(parentExpression);
//     children.push_back(move(child));
// }

void Radical::evaluateConstants(){
    for (int i = 0; i < children.size(); i ++){
        children[i]->evaluateConstants();
    }
}

void Radical::expandExponent(Symbol* parent){return;}

void Radical::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    // shared_ptr<Symbol> null;
    // return null;
    return;
}

void Radical::sumLikeTerms(){
    for (shared_ptr<Symbol> child : children){
        child->sumLikeTerms();
    }
}

shared_ptr<Symbol> Radical::copy(){

    shared_ptr<Symbol> copy = make_shared<Radical>(sign);
    vector<shared_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        shared_ptr<Symbol> copied = children[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    
    copy->setIndex(index);
    return copy;
}

shared_ptr<Symbol> Radical::sanitise(){
    
}

string Radical::toString(bool hasParent){
    string ret = "";
    for (int i = 0; i < children.size(); i ++){
        if (i < children.size() - 1){
            ret += children[i]->toString(true) + 'v';
        }else{
            ret += children[i]->toString(true);
        }
    }
    if (!sign){
        ret = "-(" + ret + ')';
    }else{
        // if (hasParent && !operands[1]->isAtomic()){
        //     ret = '(' + ret + ')';
        // }
    }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }else if(isTarget){
        ret = '(' + ret + ')';
    }
    // if (parent != nullptr){
    //     ret = '(' + ret + ')';
    // }
    // if (auxOp != nullptr && includeAuxilliaries){
    //     ret = auxOp->toString(ret);
    // }
    return ret;
}
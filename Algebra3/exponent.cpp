
#include "exponent.h"
#include "expressionComponents.h"

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

// void Exponent::appendChild(shared_ptr<Symbol>& child){
//     child->setIndex(children.size());
//     child->setParentExpression(parentExpression);
//     children.push_back(move(child));
// }

void Exponent::expandExponent(Symbol* parent){

    if (!children[1]->isAtomicExponent()){
        children[1]->expandAsExponent(*children[0], this, parent);
        
        // if (parent){
        //     // replace 'this' with 'expanded' via parentExpression
        //     parentExpression->replaceNode(this, expanded);
        // }else{
        //     // set 'root' to 'expanded'
        //     parentExpression->setRoot(expanded);
        // }
    }
    return;
}


void Exponent::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    if (!children[1]->isAtomicExponent()){
        children[1]->expandAsExponent(*children[0], this, parent);
        
        // if (parent){
        //     // replace 'this' with 'expanded' via parentExpression
        //     parentExpression->replaceNode(this, expanded);
        // }else{
        //     // set 'root' to 'expanded'
        //     parentExpression->setRoot(expanded);
        // }
        
    }
    parent->expandExponent(grandparent);
    // return this->copy();
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
        // if (hasParent && !operands[0]->isAtomic()){
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
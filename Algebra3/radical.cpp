
#include "radical.h"
#include "expressionComponents.h"

Radical::Radical(): Operation('v'){}

Radical::Radical(bool sign): Operation('v', sign){}

Radical::Radical(bool sign, vector<unique_ptr<Symbol>>& children): Operation('v', sign, children){}

Radical::Radical(bool sign, shared_ptr<Expression>& parentExpression): Operation('v', sign, parentExpression){}

Radical::Radical(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('v', sign, children, parentExpression){}

int Radical::getValue(){return 0;}

bool Radical::isAtomicExponent(){return true;}

bool Radical::isAtomicNumerator(){return true;}

void Radical::expandExponent(Symbol* parent){return;}

void Radical::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    // unique_ptr<Symbol> null;
    // return null;
    return;
}

unique_ptr<Symbol> Radical::copy(){

    unique_ptr<Symbol> copy = make_unique<Radical>(sign);
    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        unique_ptr<Symbol> copied = children[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    
    copy->setIndex(index);
    return copy;
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
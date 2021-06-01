#include "constant.h"
#include "expressionComponents.h"

Constant::Constant(): Symbol(){}

Constant::Constant(int value): Symbol(value), value(value){}

Constant::Constant(bool sign, int value): Symbol(value, sign), value(value){}

// Constant::Constant(unique_ptr<AuxOp>& auxOp, int value): Symbol(value, auxOp), value(value){}

// Constant::Constant(bool sign, unique_ptr<AuxOp>& auxOp, int value): Symbol(value, sign, auxOp), value(value){}



int Constant::getValue(){return value;}

bool Constant::isAtomic(){return true;}

void Constant::appendChild(unique_ptr<Symbol>& child){return;}

void Constant::appendChildren(vector<unique_ptr<Symbol>>& children){return;}

void Constant::appendChildren(vector<unique_ptr<Symbol>>& children, int n){return;}

void Constant::replaceChild(unique_ptr<Symbol>& child, int n){return;}

void Constant::removeChild(unique_ptr<Symbol>& child){return;}

void Constant::removeChild(int n){return;}



unique_ptr<Symbol>& Constant::getChild(int n){}

vector<unique_ptr<Symbol>>& Constant::getAllChildren(){}

vector<unique_ptr<Symbol>> Constant::duplicateChildren(){}

vector<unique_ptr<Symbol>> Constant::duplicateChildren(int start, int end){}

void Constant::expandExponent(Symbol* parent){
    // unique_ptr<Symbol> copy = this->copy();
    // return copy;
    return;
}

void Constant::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    unique_ptr<Symbol> root = make_unique<MulOp>();
    for (int i = 0; i < value; i ++){
        unique_ptr<Symbol> copy = base.copy();
        root->appendChild(copy);
    }
    grandparent->replaceChild(root, parent->getIndex());
    return;
}

unique_ptr<Symbol> Constant::copy(){

    // unique_ptr<Symbol> copy;
    // if (auxOp.get() == nullptr){
    //     copy = make_unique<Constant>(sign, value);
    // }else{
    //     unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
    //     copy = make_unique<Constant>(sign, copiedAuxOp, value);
    // }
    unique_ptr<Symbol> copy = make_unique<Constant>(sign, value);
    copy->setIndex(index);
    return copy;
}

string Constant::toString(bool hasParent){
    string ret = std::to_string(value);
    if (!sign){
        ret = '-' + ret;
    }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }

    return ret;
}

string Constant::toString(int depth, int offset){

    string str = "";
    int spaces = depth * offset;
    for (int i = 0; i < spaces; i ++){
        str += ' ';
    }
    if (!sign){
        str += '-' + std::to_string(value);
    }else{
        str += std::to_string(value);
    }
    
    return str;


}
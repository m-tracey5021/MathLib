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

void Constant::removeChild(unique_ptr<Symbol>& child){return;}

void Constant::removeChild(int n){return;}

unique_ptr<Symbol>& Constant::getChild(int n){}

vector<unique_ptr<Symbol>>& Constant::getAllChildren(){}

vector<unique_ptr<Symbol>> Constant::duplicateChildren(){}

vector<unique_ptr<Symbol>> Constant::duplicateChildren(int start, int end){}

unique_ptr<Symbol> Constant::expandExponent(){
    unique_ptr<Symbol> copy = this->copy();
    return copy;
}

unique_ptr<Symbol> Constant::expandAsExponent(unique_ptr<Symbol>& base){
    unique_ptr<Symbol> root = make_unique<MulOp>();
    for (int i = 0; i < value; i ++){
        unique_ptr<Symbol> copy = base->copy();
        root->appendChild(copy);
    }
    return root;
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
    return copy;
}

string Constant::toString(){
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
#include "mulOp.h"

MulOp::MulOp(): Operation('*'){}

MulOp::MulOp(bool sign): Operation('*', sign){}

MulOp::MulOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('*', sign, operands){}

// MulOp::MulOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('*', true, auxOp, operands){}

// MulOp::MulOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('*', sign, auxOp, operands){}

int MulOp::getCoeff(){
    int coeff = 0;
    for (int i = 0; i < operands.size(); i ++){
        int val = operands[i]->getValue();
        if (val){
            if (!coeff){
                coeff = val;
            }else{
                coeff = coeff * val;
            }
        }
    }
    return coeff;
}

int MulOp::getValue(){return 0;}

unique_ptr<Symbol>& MulOp::expandExponent(){}

unique_ptr<Symbol>& MulOp::expandAsExponent(unique_ptr<Symbol>& base){
    unique_ptr<Symbol> newRoot = make_unique<MulOp>();
    unique_ptr<Symbol> exponent = make_unique<Exponent>();
    
    int coeff = getCoeff();
    for (int i = 0; i < coeff; i ++){

    }
    
}

unique_ptr<Symbol> MulOp::copy(){

    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    // unique_ptr<Symbol> copy;
    // if (auxOp.get() == nullptr){
    //     copy = make_unique<MulOp>(sign, copiedOperands);
    // }else{
    //     unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
    //     copy = make_unique<MulOp>(sign, copiedAuxOp, copiedOperands);
    // }
    unique_ptr<Symbol> copy = make_unique<MulOp>(sign, copiedOperands);
    return copy;
}

string MulOp::toString(){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        ret += operands[i]->toString();
    }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }
    // if (parent != nullptr){
    //     ret = '(' + ret + ')';
    // }
    // if (auxOp != nullptr && includeAuxilliaries){
    //     ret = auxOp->toString(ret);
    // }
    return ret;
}
#include "mulOp.h"

MulOp::MulOp(): Operation('*'){}

MulOp::MulOp(bool sign): Operation('*', sign){}

MulOp::MulOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('*', sign, operands){}

MulOp::MulOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('*', true, auxOp, operands){}

MulOp::MulOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('*', sign, auxOp, operands){}

unique_ptr<Symbol> MulOp::copy(){

    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    unique_ptr<Symbol> copy;
    if (auxOp.get() == nullptr){
        copy = make_unique<MulOp>(sign, copiedOperands);
    }else{
        unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
        copy = make_unique<MulOp>(sign, copiedAuxOp, copiedOperands);
    }
    return copy;
}

string MulOp::toString(){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        ret += operands[i]->toString();
    }
    return ret;
}
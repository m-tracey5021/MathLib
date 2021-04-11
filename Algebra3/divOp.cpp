#include "divOp.h"

DivOp::DivOp(): Operation('/'){}

DivOp::DivOp(bool sign): Operation('/', sign){}

DivOp::DivOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('/', sign, operands){}

DivOp::DivOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('/', true, auxOp, operands){}

DivOp::DivOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('/', sign, auxOp, operands){}

unique_ptr<Symbol> DivOp::copy(){
    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    unique_ptr<Symbol> copy;
    if (auxOp.get() == nullptr){
        copy = make_unique<DivOp>(sign, copiedOperands);
    }else{
        unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
        copy = make_unique<DivOp>(sign, copiedAuxOp, copiedOperands);
    }
    return copy;
}

string DivOp::toString(){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        if (i < operands.size() - 1){
            ret += operands[i]->toString() + '/';
        }else{
            ret += operands[i]->toString();
        }
    }
    return ret;
}
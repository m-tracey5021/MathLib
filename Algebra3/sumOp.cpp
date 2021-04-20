#include "sumOp.h"

SumOp::SumOp(): Operation('+'){}

SumOp::SumOp(bool sign): Operation('+', sign){}

SumOp::SumOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('+', sign, operands){}

SumOp::SumOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('+', true, auxOp, operands){}

SumOp::SumOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('+', sign, auxOp, operands){}

unique_ptr<Symbol> SumOp::copy(){

    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    unique_ptr<Symbol> copy;
    if (auxOp.get() == nullptr){
        copy = make_unique<SumOp>(sign, copiedOperands);
    }else{
        unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
        copy = make_unique<SumOp>(sign, copiedAuxOp, copiedOperands);
    }
    return copy;
}

string SumOp::toString(bool includeAuxilliaries){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        if (i < operands.size() - 1){
            ret += operands[i]->toString(true) + '+';
        }else{
            ret += operands[i]->toString(true);
        }
    }
    if (parent != nullptr){
        ret = '(' + ret + ')';
    }
    if (auxOp != nullptr && includeAuxilliaries){
        ret = auxOp->toString(ret);
    }
    return ret;
}
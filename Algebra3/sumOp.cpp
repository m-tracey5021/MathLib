#include "sumOp.h"

SumOp::SumOp(): Operation('+'){}

SumOp::SumOp(bool sign): Operation('+', sign){}

SumOp::SumOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('+', sign, operands){}

// SumOp::SumOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('+', true, auxOp, operands){}

// SumOp::SumOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('+', sign, auxOp, operands){}

int SumOp::getValue(){return 0;}

unique_ptr<Symbol>& SumOp::expandExponent(){}

unique_ptr<Symbol>& SumOp::expandAsExponent(unique_ptr<Symbol>& base){}

unique_ptr<Symbol> SumOp::copy(){

    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    // unique_ptr<Symbol> copy;
    // if (auxOp.get() == nullptr){
    //     copy = make_unique<SumOp>(sign, copiedOperands);
    // }else{
    //     unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
    //     copy = make_unique<SumOp>(sign, copiedAuxOp, copiedOperands);
    // }
    unique_ptr<Symbol> copy = make_unique<SumOp>(sign, copiedOperands);
    return copy;
}

string SumOp::toString(){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        if (i < operands.size() - 1){
            ret += operands[i]->toString() + '+';
        }else{
            ret += operands[i]->toString();
        }
    }
    if (parent != nullptr){
        if (isExponent){
            ret = '{' + ret + '}';
        }else if(isRadical){
            ret = '[' + ret + ']';
        }else{
            ret = '(' + ret + ')';
        }
        
    }
    // if (auxOp != nullptr && includeAuxilliaries){
    //     ret = auxOp->toString(ret);
    // }
    return ret;
}
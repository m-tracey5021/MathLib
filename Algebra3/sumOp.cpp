#include "sumOp.h"

SumOp::SumOp(): Operation('+'){}

SumOp::SumOp(bool sign): Operation('+', sign){}

SumOp::SumOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('+', sign, operands){}

// SumOp::SumOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('+', true, auxOp, operands){}

// SumOp::SumOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('+', sign, auxOp, operands){}

int SumOp::getValue(){return 0;}

unique_ptr<Symbol>& SumOp::expandExponent(){}

unique_ptr<Symbol>& SumOp::expandAsExponent(unique_ptr<Symbol>& base){
    unique_ptr<Symbol> root = make_unique<MulOp>();
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> op = make_unique<Exponent>();
        unique_ptr<Symbol> target = base->copy();
        unique_ptr<Symbol> exponent = operands[i]->copy();
        target->setAsTarget(true);
        exponent->setAsExponent(true);
        op->appendChild(target);
        op->appendChild(exponent);
        root->appendChild(op);
    }
    return root;
}

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
        if (i != 0){
            if (operands[i]->getSign()){
                ret += '+' + operands[i]->toString();
            }else{
                ret += operands[i]->toString();
            }
            
        }else{
            ret += operands[i]->toString();
        }
    }
    if (!sign){
        ret = "-(" + ret + ')';
    }else{
        if (parent != nullptr){
            ret = '(' + ret + ')';
        }
    }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }

    // if (auxOp != nullptr && includeAuxilliaries){
    //     ret = auxOp->toString(ret);
    // }
    return ret;
}

// string SumOp::toString(int& depth, int offset){
//     str += '\n';

//     int spaces = depth * offset;
//     for (int i = 0; i < spaces; i ++){
//         str += ' ';
//     }
//     if (!sign){
//         str += "-(+)";
//     }else{
//         str += '+';
//     }
//     depth ++;
//     for (int i = 0; i < operands.size(); i ++){
//         str += operands[i]->toString(str, depth, offset);
//     }
    
//     return str;
//     return "";

// }
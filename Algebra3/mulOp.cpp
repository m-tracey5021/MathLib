#include "mulOp.h"

MulOp::MulOp(): Operation('*'){}

MulOp::MulOp(bool sign): Operation('*', sign){}

MulOp::MulOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('*', sign, operands){}


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

unique_ptr<Symbol>& MulOp::expandAsExponent(unique_ptr<Symbol>& base){ // x^(2y) x = base 2y = operands y = duplicates
    unique_ptr<Symbol> root = make_unique<MulOp>();
    vector<unique_ptr<Symbol>> duplicates = duplicateChildren();
    int coeff = getCoeff();
    for (int i = 0; i < coeff; i ++){
        unique_ptr<Symbol> op = make_unique<Exponent>();
        unique_ptr<Symbol> target = base->copy();
        unique_ptr<Symbol> exponent;
        if (duplicates.size() == 1){
            exponent = duplicates[0]->copy();
        }else{
            exponent = make_unique<MulOp>();
            for (int j = 0; j < duplicates.size(); j ++){
                unique_ptr<Symbol> exponentOperand = duplicates[j]->copy();
                exponent->appendChild(exponentOperand);
            }
        }
        op->appendChild(target);
        op->appendChild(exponent);
        root->appendChild(op);
    }
    return root;
    
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
    if (!sign){
        ret = '-' + ret;
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

// string MulOp::toString(int& depth, int offset){
//     str += '\n';

//     int spaces = depth * offset;
//     for (int i = 0; i < spaces; i ++){
//         str += ' ';
//     }
//     if (!sign){
//         str += "-(*)";
//     }else{
//         str += '*';
//     }
//     depth ++;
//     for (int i = 0; i < operands.size(); i ++){
//         str += operands[i]->toString(str, depth, offset);
//     }
    
//     return str;

//     return "";
// }
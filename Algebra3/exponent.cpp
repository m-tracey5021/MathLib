// #include "exponent.h"

// Exponent::Exponent(): AuxOp(){}

// Exponent::Exponent(unique_ptr<Symbol>& root): AuxOp(root){}

// unique_ptr<AuxOp> Exponent::copy(){
//     unique_ptr<Symbol> copiedRoot = root->copy();
//     unique_ptr<AuxOp> copy = make_unique<Exponent>(copiedRoot);
//     return copy;
// }

// string Exponent::toString(string target){
//     target += "^{" + root->toString(false) + '}';
//     unique_ptr<AuxOp>& nextAuxillary = root->getAuxillary();
//     if (nextAuxillary != nullptr){
//         target = nextAuxillary->toString(target);
//     }
//     return target;
// }

#include "exponent.h"

Exponent::Exponent(): Operation('^'){}

Exponent::Exponent(bool sign): Operation('^', sign){}

Exponent::Exponent(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('^', sign, operands){}

Exponent::Exponent(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('^', true, auxOp, operands){}

Exponent::Exponent(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('^', sign, auxOp, operands){}

unique_ptr<Symbol> Exponent::copy(){

    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    unique_ptr<Symbol> copy;
    if (auxOp.get() == nullptr){
        copy = make_unique<Exponent>(sign, copiedOperands);
    }else{
        unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
        copy = make_unique<Exponent>(sign, copiedAuxOp, copiedOperands);
    }
    return copy;
}

string Exponent::toString(bool includeAuxilliaries){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        if (i < operands.size() - 1){
            ret += operands[i]->toString(true) + "^{";
        }else{
            ret += operands[i]->toString(true) + '}';
        }
    }
    if (parent != nullptr){
        ret = '(' + ret + ')';
    }
    // if (auxOp != nullptr && includeAuxilliaries){
    //     ret = auxOp->toString(ret);
    // }
    return ret;
}
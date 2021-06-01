#include "mulOp.h"
#include "expressionComponents.h"

MulOp::MulOp(): Operation('*'){}

MulOp::MulOp(bool sign): Operation('*', sign){}

MulOp::MulOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('*', sign, operands){}


// int MulOp::getCoeff(){
//     int coeff = 0;
//     for (int i = 0; i < operands.size(); i ++){
//         int val = operands[i]->getValue();
//         if (val){
//             if (!coeff){
//                 coeff = val;
//             }else{
//                 coeff = coeff * val;
//             }
//         }
//     }
//     return coeff;
// }

unique_ptr<Symbol> MulOp::extractCoeff(){
    int coeffVal = 1;
    for (int i = 0; i < operands.size(); i ++){
        int val = operands[i]->getValue();
        if (val > 0 && operands[i]->isAtomic() && !operands[i]->getIsTarget()){
            
            coeffVal = coeffVal * val;
            removeChild(i);
        }
    }
    unique_ptr<Symbol> coeff = make_unique<Constant>(coeffVal);
    return coeff;
}

int MulOp::getValue(){return 0;}

void MulOp::expandExponent(Symbol* parent){
    // unique_ptr<Symbol> copy = this->copy();
    // vector<unique_ptr<Symbol>>& copiedOperands = copy->getAllChildren();
    // for (int i = 0; i < copiedOperands.size(); i ++){
    //     copiedOperands[i] = move(copiedOperands[i]->expandExponent(this));
    // }
    // return copy;
    for (int i = 0; i < operands.size(); i ++){
        operands[i]->expandExponent(this);
    }
    return;
}

void MulOp::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){ // x^(2y) x = base 2y = operands y = duplicates
    

    vector<unique_ptr<Symbol>> ops;
    unique_ptr<Symbol> coeff = extractCoeff();
    for (int i = 0; i < coeff->getValue(); i ++){
        unique_ptr<Symbol> op = make_unique<Exponent>();
        unique_ptr<Symbol> target = base.copy();
        unique_ptr<Symbol> exponent;
        if (operands.size() == 1){
            exponent = operands[0]->copy();
        }else{
            exponent = make_unique<MulOp>();
            for (int j = 0; j < operands.size(); j ++){
                unique_ptr<Symbol> exponentOperand = operands[j]->copy();
                exponent->appendChild(exponentOperand);
            }
        }
        op->appendChild(target);
        op->appendChild(exponent);
        ops.push_back(move(op));
        //root->appendChild(op);
    }
    if (grandparent->getSymbol() == '*'){
        int index = parent->getIndex();
        grandparent->removeChild(index);
        grandparent->appendChildren(ops, index);
        
        // unique_ptr<Symbol> null;
        // return null;
        return;
    
    }else{
        unique_ptr<Symbol> root = make_unique<MulOp>();
        root->appendChildren(ops);
        // return root;
        grandparent->replaceChild(root, parent->getIndex());
        return;
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
    copy->setIndex(index);
    return copy;
}

string MulOp::toString(bool hasParent){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        ret += operands[i]->toString(true);
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
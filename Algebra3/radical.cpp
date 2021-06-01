// #include "radical.h"

// Radical::Radical(): AuxOp(){}

// Radical::Radical(unique_ptr<Symbol>& root): AuxOp(root){}

// unique_ptr<AuxOp> Radical::copy(){
//     unique_ptr<Symbol> copiedRoot = root->copy();
//     unique_ptr<AuxOp> copy = make_unique<Radical>(copiedRoot);
//     return copy;
// }

// string Radical::toString(string target){
//     target = '[' + root->toString(false) + "]v" + target;
//     unique_ptr<AuxOp>& nextAuxillary = root->getAuxillary();
//     if (nextAuxillary != nullptr){
//         target = nextAuxillary->toString(target);
//     }
//     return target;
// }

#include "radical.h"
#include "expressionComponents.h"

Radical::Radical(): Operation('v'){}

Radical::Radical(bool sign): Operation('v', sign){}

Radical::Radical(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('v', sign, operands){}

// Radical::Radical(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('v', true, auxOp, operands){}

// Radical::Radical(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('v', sign, auxOp, operands){}

int Radical::getValue(){return 0;}

void Radical::expandExponent(Symbol* parent){return;}

void Radical::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){return;}

unique_ptr<Symbol> Radical::copy(){

    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    unique_ptr<Symbol> copy = make_unique<Radical>(sign, copiedOperands);
    copy->setIndex(index);
    return copy;
}

string Radical::toString(bool hasParent){
    string ret = "";
    // REDO
    for (int i = 0; i < operands.size(); i ++){
        if (i < operands.size() - 1){
            ret += operands[i]->toString(true) + 'v';
        }else{
            ret += operands[i]->toString(true);
        }
    }
    if (!sign){
        ret = "-(" + ret + ')';
    }else{
        if (hasParent && !operands[1]->isAtomic()){
            ret = '(' + ret + ')';
        }
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
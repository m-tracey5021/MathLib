#include "divOp.h"
#include "expressionComponents.h"

DivOp::DivOp(): Operation('/'){}

DivOp::DivOp(bool sign): Operation('/', sign){}

DivOp::DivOp(bool sign, vector<unique_ptr<Symbol>>& operands): Operation('/', sign, operands){}

// DivOp::DivOp(unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('/', true, auxOp, operands){}

// DivOp::DivOp(bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Operation('/', sign, auxOp, operands){}

int DivOp::getValue(){return 0;}

void DivOp::expandExponent(Symbol* parent){
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

void DivOp::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    for (int i = 0; i < operands.size(); i ++){
        operands[i]->expandExponent(this);
    }
    unique_ptr<Symbol> root;
    unique_ptr<Symbol> target;
    unique_ptr<Symbol> exponent;
    int numeratorValue = operands[0]->getValue();
    if (numeratorValue <= 1){

        // unique_ptr<Symbol> copy = parent->copy(); // return null here if not able to copy, then check for null in function that calls this
        // unique_ptr<Symbol> null;
        // return null;
        return;
        
    }else{
        root = make_unique<MulOp>();
        for (int i = 0; i < numeratorValue; i ++){
            unique_ptr<Symbol> numerator = make_unique<Constant>(1);
            unique_ptr<Symbol> denominator = operands[1]->copy();

            unique_ptr<Symbol> op = make_unique<Exponent>();
            target = base.copy();
            exponent = make_unique<DivOp>(sign);

            exponent->appendChild(numerator);
            exponent->appendChild(denominator);
            target->setAsTarget(true);
            exponent->setAsExponent(true);
            op->appendChild(target);
            op->appendChild(exponent);
            root->appendChild(op);
        }
        // return root;
        grandparent->replaceChild(root, parent->getIndex());
        return;
    }
}

unique_ptr<Symbol> DivOp::copy(){

    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> copied = operands[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    // unique_ptr<Symbol> copy;
    // if (auxOp.get() == nullptr){
    //     copy = make_unique<DivOp>(sign, copiedOperands);
    // }else{
    //     unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
    //     copy = make_unique<DivOp>(sign, copiedAuxOp, copiedOperands);
    // }
    unique_ptr<Symbol> copy = make_unique<DivOp>(sign, copiedOperands);
    copy->setIndex(index);
    return copy;
}

string DivOp::toString(bool hasParent){
    string ret = "";
    for (int i = 0; i < operands.size(); i ++){
        if (i < operands.size() - 1){
            ret += operands[i]->toString(true) + '/';
        }else{
            ret += operands[i]->toString(true);
        }
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
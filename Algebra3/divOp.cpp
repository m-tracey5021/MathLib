#include "divOp.h"
#include "expressionComponents.h"

DivOp::DivOp(): Operation('/'){}

DivOp::DivOp(bool sign): Operation('/', sign){}

DivOp::DivOp(bool sign, vector<unique_ptr<Symbol>>& children): Operation('/', sign, children){}

DivOp::DivOp(bool sign, shared_ptr<Expression>& parentExpression): Operation('/', sign, parentExpression){}

DivOp::DivOp(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('/', sign, children, parentExpression){}

int DivOp::getValue(){return 0;}

bool DivOp::isAtomicExponent(){
    if (children[0]->isAtomicNumerator()){
        return true;
    }else{
        return false;
    }
}

bool DivOp::isAtomicNumerator(){return true;}

void DivOp::expandExponent(Symbol* parent){
    for (int i = 0; i < children.size(); i ++){
        children[i]->expandExponent(this);
    }
    return;
}

void DivOp::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    for (int i = 0; i < children.size(); i ++){
        children[i]->expandExponent(this);
    }
    unique_ptr<Symbol> root;
    unique_ptr<Symbol> target;
    unique_ptr<Symbol> exponent;
    int numeratorValue = children[0]->getValue();
    if (numeratorValue <= 1){

        // unique_ptr<Symbol> null;
        // return null;
        return;
        
    }else{
        root = make_unique<MulOp>();
        vector<unique_ptr<Symbol>> ops;
        for (int i = 0; i < numeratorValue; i ++){
            unique_ptr<Symbol> numerator = make_unique<Constant>(1);
            unique_ptr<Symbol> denominator = children[1]->copy();

            unique_ptr<Symbol> op = make_unique<Exponent>();
            target = base.copy();
            exponent = make_unique<DivOp>(sign);

            exponent->appendChild(numerator);
            exponent->appendChild(denominator);
            target->setIsTarget(true);
            exponent->setIsExponent(true);
            op->appendChild(target);
            op->appendChild(exponent);
            root->appendChild(op);
        }
        // return root;
        parentExpression->replaceNode(parent, root);
    }
}

unique_ptr<Symbol> DivOp::copy(){

    unique_ptr<Symbol> copy = make_unique<DivOp>(sign);
    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        unique_ptr<Symbol> copied = children[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    
    copy->setIndex(index);
    return copy;
}

string DivOp::toString(bool hasParent){
    string ret = "";
    for (int i = 0; i < children.size(); i ++){
        if (i < children.size() - 1){
            ret += children[i]->toString(true) + '/';
        }else{
            ret += children[i]->toString(true);
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
#include "divOp.h"
#include "expressionComponents.h"

DivOp::DivOp(): Operation('/'){}

DivOp::DivOp(bool sign): Operation('/', sign){}

DivOp::DivOp(bool sign, vector<shared_ptr<Symbol>>& children): Operation('/', sign, children){}

DivOp::DivOp(bool sign, shared_ptr<Expression>& parentExpression): Operation('/', sign, parentExpression){}

DivOp::DivOp(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('/', sign, children, parentExpression){}

void DivOp::accept(Visitor* visitor){
    visitor->Visit(this);
}

bool DivOp::isAtomicExponent(){
    if (children[0]->isAtomicNumerator()){
        return true;
    }else{
        return false;
    }
}

bool DivOp::isAtomicNumerator(){return true;}

bool DivOp::isEqual(Symbol* other){}

// void DivOp::appendChild(shared_ptr<Symbol>& child){
//     child->setIndex(children.size());
//     child->setParentExpression(parentExpression);
//     children.push_back(move(child));
// }

void DivOp::evaluateConstants(){
    int total;
    bool totalSign;
    optional<int> num = children[0]->getValue();
    optional<int> denom = children[1]->getValue();
    if (!num){
        children[0]->evaluateConstants();
        num = children[0]->getValue();
    }
    if (!denom){
        children[1]->evaluateConstants();
        denom = children[1]->getValue();
    }
    if (children[0]->getSign() == children[1]->getSign()){
        totalSign = true;
    }else{
        totalSign = false;
    }
    if (num && denom){
        int result = *num / *denom;
        shared_ptr<Symbol> divided = make_shared<Constant>(totalSign, result);
        parentExpression->replaceNode(this, divided);
    }
}

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
    shared_ptr<Symbol> root;
    shared_ptr<Symbol> target;
    shared_ptr<Symbol> exponent;
    if (children[0]->getValue()){
        int numeratorValue = *children[0]->getValue();
        if (numeratorValue <= 1){

            // shared_ptr<Symbol> null;
            // return null;
            return;
            
        }else{
            root = make_shared<MulOp>();
            vector<shared_ptr<Symbol>> ops;
            for (int i = 0; i < numeratorValue; i ++){
                shared_ptr<Symbol> numerator = make_shared<Constant>(1);
                shared_ptr<Symbol> denominator = children[1]->copy();

                shared_ptr<Symbol> op = make_shared<Exponent>();
                target = base.copy();
                exponent = make_shared<DivOp>(sign);

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
    
}

shared_ptr<Symbol> DivOp::copy(){

    shared_ptr<Symbol> copy = make_shared<DivOp>(sign);
    vector<shared_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        shared_ptr<Symbol> copied = children[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    
    copy->setIndex(index);
    return copy;
}

shared_ptr<Symbol> DivOp::sanitise(){
    
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
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

int DivOp::getValue(){return 0;}

bool DivOp::isAtomicExponent(){
    if (children[0]->isAtomicNumerator()){
        return true;
    }else{
        return false;
    }
}

bool DivOp::isAtomicNumerator(){return true;}

void DivOp::appendChild(shared_ptr<Symbol>& child){
    child->setIndex(children.size());
    child->setParentExpression(parentExpression);
    children.push_back(move(child));
}

void DivOp::appendToParent(SumOp* parent){
    
}

void DivOp::appendToParent(MulOp* parent){
    
}

void DivOp::appendToParent(DivOp* parent){
    
}

void DivOp::appendToParent(Exponent* parent){
    
}

void DivOp::appendToParent(Radical* parent){
    
}

void DivOp::appendToParent(Constant* parent){
    
}

void DivOp::appendToParent(Variable* parent){
    
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
    int numeratorValue = children[0]->getValue();
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
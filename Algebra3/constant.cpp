#include "constant.h"
#include "expressionComponents.h"

Constant::Constant(): Atom(){}

Constant::Constant(int value): Atom(value), value(value){}

Constant::Constant(bool sign, int value): Atom(value, sign), value(value){}

Constant::Constant(bool sign, int value, shared_ptr<Expression>& parentExpression): Atom(value, sign, parentExpression), value(value){}

void Constant::accept(Visitor* visitor){
    visitor->Visit(this);
}

int Constant::getValue(){return value;}

bool Constant::isAtomic(){return true;}

bool Constant::isAtomicExponent(){return false;}

void Constant::appendToParent(SumOp* parent){
    
}

void Constant::appendToParent(MulOp* parent){
    
}

void Constant::appendToParent(DivOp* parent){
    
}

void Constant::appendToParent(Exponent* parent){
    
}

void Constant::appendToParent(Radical* parent){
    
}

void Constant::appendToParent(Constant* parent){
    
}

void Constant::appendToParent(Variable* parent){
    
}

bool Constant::isAtomicNumerator(){
    if (value == 1){
        return true;
    }else{
        return false;
    }
}

void Constant::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    shared_ptr<Symbol> root = make_shared<MulOp>();
    vector<shared_ptr<Symbol>> ops;
    for (int i = 0; i < value; i ++){
        shared_ptr<Symbol> copy = base.copy();
        root->appendChild(copy);
    }
    // return root;
    parentExpression->replaceNode(parent, root);
}

shared_ptr<Symbol> Constant::copy(){

    shared_ptr<Symbol> copy = make_shared<Constant>(sign, value);
    copy->setIndex(index);
    return copy;
}

string Constant::toString(bool hasParent){
    string ret = std::to_string(value);
    if (!sign){
        ret = '-' + ret;
    }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }

    return ret;
}

string Constant::toString(int depth, int offset){

    string str = "";
    int spaces = depth * offset;
    for (int i = 0; i < spaces; i ++){
        str += ' ';
    }
    if (!sign){
        str += '-' + std::to_string(value);
    }else{
        str += std::to_string(value);
    }
    
    return str;


}
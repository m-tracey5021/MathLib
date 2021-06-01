#include "variable.h"
#include "expressionComponents.h"

Variable::Variable(): Symbol(){}

Variable::Variable(char value): Symbol(value), value(value){}

Variable::Variable(bool sign, char value): Symbol(value, sign), value(value){}

// Variable::Variable(unique_ptr<AuxOp>& auxOp, char value): Symbol(value, auxOp), value(value){}

// Variable::Variable(bool sign, unique_ptr<AuxOp>& auxOp, char value): Symbol(value, sign, auxOp), value(value){}



int Variable::getValue(){return 0;}

bool Variable::isAtomic(){return true;}

void Variable::appendChild(unique_ptr<Symbol>& child){return;}

void Variable::appendChildren(vector<unique_ptr<Symbol>>& children){return;}

void Variable::appendChildren(vector<unique_ptr<Symbol>>& children, int n){return;}

void Variable::replaceChild(unique_ptr<Symbol>& child, int n){return;}

void Variable::removeChild(unique_ptr<Symbol>& child){return;}

void Variable::removeChild(int n){return;}



unique_ptr<Symbol>& Variable::getChild(int n){}

vector<unique_ptr<Symbol>>& Variable::getAllChildren(){}

vector<unique_ptr<Symbol>> Variable::duplicateChildren(){}

vector<unique_ptr<Symbol>> Variable::duplicateChildren(int start, int end){}

void Variable::expandExponent(Symbol* parent){
    // unique_ptr<Symbol> copy = this->copy();
    // return copy;
    return;
}

void Variable::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){

    // unique_ptr<Symbol> copy = parent->copy();
    // return copy;
    return;

}

unique_ptr<Symbol> Variable::copy(){
    
    // unique_ptr<Symbol> copy;
    // if (auxOp.get() == nullptr){
    //     copy = make_unique<Variable>(sign, value);
    // }else{
    //     unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
    //     copy = make_unique<Variable>(sign, copiedAuxOp, value);
    // }
    unique_ptr<Symbol> copy = make_unique<Variable>(sign, value);
    copy->setIndex(index);
    return copy;
}

string Variable::toString(bool hasParent){
    string ret = "";
    ret += value;
    if (!sign){
        ret = '-' + ret;
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

string Variable::toString(int depth, int offset){

    string str = "";
    int spaces = depth * offset;
    for (int i = 0; i < spaces; i ++){
        str += ' ';
    }
    if (!sign){
        str += '-' + value;
    }else{
        str += value;
    }
    
    return str;


}
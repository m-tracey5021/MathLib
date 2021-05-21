#include "variable.h"

Variable::Variable(): Symbol(){}

Variable::Variable(char value): Symbol(value), value(value){}

Variable::Variable(bool sign, char value): Symbol(value, sign), value(value){}

// Variable::Variable(unique_ptr<AuxOp>& auxOp, char value): Symbol(value, auxOp), value(value){}

// Variable::Variable(bool sign, unique_ptr<AuxOp>& auxOp, char value): Symbol(value, sign, auxOp), value(value){}



int Variable::getValue(){return 0;}

void Variable::appendChild(unique_ptr<Symbol>& child){}

unique_ptr<Symbol>& Variable::getNthChild(int n){}

vector<unique_ptr<Symbol>>& Variable::getAllChildren(){}

vector<unique_ptr<Symbol>> Variable::duplicateChildren(){}

vector<unique_ptr<Symbol>> Variable::duplicateChildren(int start, int end){}

unique_ptr<Symbol>& Variable::expandExponent(){}

unique_ptr<Symbol>& Variable::expandAsExponent(unique_ptr<Symbol>& base){}

unique_ptr<Symbol> Variable::copy(){
    
    // unique_ptr<Symbol> copy;
    // if (auxOp.get() == nullptr){
    //     copy = make_unique<Variable>(sign, value);
    // }else{
    //     unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
    //     copy = make_unique<Variable>(sign, copiedAuxOp, value);
    // }
    unique_ptr<Symbol> copy = make_unique<Variable>(sign, value);
    return copy;
}

string Variable::toString(){
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
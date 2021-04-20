#include "variable.h"

Variable::Variable(): Symbol(){}

Variable::Variable(char value): Symbol(value), value(value){}

Variable::Variable(bool sign, char value): Symbol(value, sign), value(value){}

Variable::Variable(unique_ptr<AuxOp>& auxOp, char value): Symbol(value, auxOp), value(value){}

Variable::Variable(bool sign, unique_ptr<AuxOp>& auxOp, char value): Symbol(value, sign, auxOp), value(value){}

void Variable::appendChild(unique_ptr<Symbol>& child){}

unique_ptr<Symbol>& Variable::getNthChild(int n){
    unique_ptr<Symbol> null;
    return null;
}

vector<unique_ptr<Symbol>>& Variable::getAllChildren(){}

unique_ptr<Symbol> Variable::copy(){
    
    unique_ptr<Symbol> copy;
    if (auxOp.get() == nullptr){
        copy = make_unique<Variable>(sign, value);
    }else{
        unique_ptr<AuxOp> copiedAuxOp = auxOp->copy();
        copy = make_unique<Variable>(sign, copiedAuxOp, value);
    }
    return copy;
}

string Variable::toString(bool includeAuxilliaries){
    string ret = "";
    ret += value;
    if (auxOp != nullptr && includeAuxilliaries){
        ret = auxOp->toString(ret);
    }
    return ret;
}
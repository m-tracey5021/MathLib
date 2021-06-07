#include "variable.h"
#include "expressionComponents.h"

Variable::Variable(): Atom(){}

Variable::Variable(char value): Atom(value), value(value){}

Variable::Variable(bool sign, char value): Atom(value, sign), value(value){}

Variable::Variable(bool sign, char value, shared_ptr<Expression>& parentExpression): Atom(value, sign, parentExpression), value(value){}

int Variable::getValue(){return 0;}

bool Variable::isAtomic(){return true;}

bool Variable::isAtomicExponent(){return true;}

bool Variable::isAtomicNumerator(){return true;}

void Variable::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){

    // unique_ptr<Symbol> null;
    // return null;
    return;

}

unique_ptr<Symbol> Variable::copy(){

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
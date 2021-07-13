#include "variable.h"
#include "expressionComponents.h"
#include "Visitors/equalTo.h"

Variable::Variable(): Atom(){}

Variable::Variable(char value): Atom(value), value(value){}

Variable::Variable(bool sign, char value): Atom(value, sign), value(value){}

Variable::Variable(bool sign, char value, shared_ptr<Expression>& parentExpression): Atom(value, sign, parentExpression), value(value){}

void Variable::accept(Visitor* visitor){
    visitor->Visit(this);
}

optional<int> Variable::getValue(){
    optional<int> result = nullopt;
    return result;
}

bool Variable::isAtomic(){return true;}

bool Variable::isAtomicExponent(){return true;}

bool Variable::isAtomicNumerator(){return true;}

bool Variable::isEqual(Symbol* other){
    shared_ptr<EqualToVariable> equal = make_shared<EqualToVariable>(*this);
    other->accept(equal.get());
    return equal->isEqual;
}

bool Variable::isLikeTerm(Symbol* other){return false;}

void Variable::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){

    // shared_ptr<Symbol> null;
    // return null;
    return;

}

void Variable::sumLikeTerms(){return;}

shared_ptr<Symbol> Variable::copy(){

    shared_ptr<Symbol> copy = make_shared<Variable>(sign, value);
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
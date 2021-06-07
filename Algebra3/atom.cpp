#include "atom.h"
#include "expressionComponents.h"

Atom::Atom(): Symbol(){}

Atom::Atom(char value): Symbol(value){}

Atom::Atom(char value, bool sign): Symbol(value, sign){}

Atom::Atom(char value, bool sign, shared_ptr<Expression>& parentExpression): Symbol(value, sign, parentExpression){}

// Atom::Atom(unique_ptr<AuxOp>& auxOp, char value): Symbol(value, auxOp), value(value){}

// Atom::Atom(bool sign, unique_ptr<AuxOp>& auxOp, char value): Symbol(value, sign, auxOp), value(value){}



int Atom::getValue(){return 0;}

bool Atom::isAtomic(){return true;}

bool Atom::isAtomicExponent(){return true;}

bool Atom::isAtomicNumerator(){return true;}

void Atom::setChildren(vector<unique_ptr<Symbol>>& children){return;}

void Atom::appendChild(unique_ptr<Symbol>& child){return;}

void Atom::appendChildren(vector<unique_ptr<Symbol>>& children){return;}

void Atom::appendChildren(vector<unique_ptr<Symbol>>& children, int n){return;}

void Atom::replaceChild(unique_ptr<Symbol>& child, int n){return;}
void Atom::replaceChild(unique_ptr<SumOp>& child, int n){return;}
void Atom::replaceChild(unique_ptr<MulOp>& child, int n){return;}

void Atom::removeChild(unique_ptr<Symbol>& child){return;}

void Atom::removeChild(int n){return;}



unique_ptr<Symbol>& Atom::getChild(int n){
    
}

vector<unique_ptr<Symbol>>& Atom::getChildren(){
    return children;
}

vector<unique_ptr<Symbol>> Atom::duplicateChildren(){
    vector<unique_ptr<Symbol>> empty;
    return empty;
}

vector<unique_ptr<Symbol>> Atom::duplicateChildren(int start, int end){
    vector<unique_ptr<Symbol>> empty;
    return empty;
}

void Atom::expandExponent(Symbol* parent){return;}

void Atom::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){

    // unique_ptr<Symbol> null;
    // return null;
    return;

}

unique_ptr<Symbol> Atom::copy(){}

string Atom::toString(bool hasParent){}

string Atom::toString(int depth, int offset){}
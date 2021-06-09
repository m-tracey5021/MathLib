#include "atom.h"
#include "expressionComponents.h"

Atom::Atom(): Symbol(){}

Atom::Atom(char value): Symbol(value){}

Atom::Atom(char value, bool sign): Symbol(value, sign){}

Atom::Atom(char value, bool sign, shared_ptr<Expression>& parentExpression): Symbol(value, sign, parentExpression){}

// Atom::Atom(shared_ptr<AuxOp>& auxOp, char value): Symbol(value, auxOp), value(value){}

// Atom::Atom(bool sign, shared_ptr<AuxOp>& auxOp, char value): Symbol(value, sign, auxOp), value(value){}



int Atom::getValue(){return 0;}

bool Atom::isAtomic(){return true;}

bool Atom::isAtomicExponent(){return true;}

bool Atom::isAtomicNumerator(){return true;}

void Atom::setChildren(vector<shared_ptr<Symbol>>& children){return;}

void Atom::appendChild(shared_ptr<Symbol>& child){return;}

void Atom::appendChildren(vector<shared_ptr<Symbol>>& children){return;}

void Atom::appendChildren(vector<shared_ptr<Symbol>>& children, int n){return;}

void Atom::replaceChild(shared_ptr<Symbol>& child, int n){return;}
void Atom::replaceChild(shared_ptr<SumOp>& child, int n){return;}
void Atom::replaceChild(shared_ptr<MulOp>& child, int n){return;}

void Atom::removeChild(shared_ptr<Symbol>& child){return;}

void Atom::removeChild(int n){return;}



// shared_ptr<Symbol>& Atom::getChild(int n){
    
// }

// vector<shared_ptr<Symbol>>& Atom::getChildren(){
//     return children;
// }

vector<shared_ptr<Symbol>> Atom::duplicateChildren(){
    vector<shared_ptr<Symbol>> empty;
    return empty;
}

vector<shared_ptr<Symbol>> Atom::duplicateChildren(int start, int end){
    vector<shared_ptr<Symbol>> empty;
    return empty;
}

void Atom::expandExponent(Symbol* parent){return;}

void Atom::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){

    // shared_ptr<Symbol> null;
    // return null;
    return;

}

shared_ptr<Symbol> Atom::copy(){}

string Atom::toString(bool hasParent){}

string Atom::toString(int depth, int offset){}
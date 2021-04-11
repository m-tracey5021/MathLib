#include "exponent.h"

Exponent::Exponent(): AuxOp(){}

Exponent::Exponent(unique_ptr<Symbol>& rootSymbol): AuxOp(rootSymbol){}

unique_ptr<AuxOp> Exponent::copy(){
    unique_ptr<Symbol> copiedRootSymbol = rootSymbol->copy();
    unique_ptr<AuxOp> copy = make_unique<Exponent>(copiedRootSymbol);
    return copy;
}

string Exponent::toString(){return "";}
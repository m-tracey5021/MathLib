#include "exponent.h"

Exponent::Exponent(): AuxOp(){}

Exponent::Exponent(unique_ptr<Symbol>& root): AuxOp(root){}

unique_ptr<AuxOp> Exponent::copy(){
    unique_ptr<Symbol> copiedRoot = root->copy();
    unique_ptr<AuxOp> copy = make_unique<Exponent>(copiedRoot);
    return copy;
}

string Exponent::toString(string target){
    target += "^{" + root->toString() + '}';
    unique_ptr<AuxOp>& nextAuxillary = root->getAuxillary();
    if (nextAuxillary != nullptr){
        target = nextAuxillary->toString(target);
    }
    return target;
}
#include "radical.h"

Radical::Radical(): AuxOp(){}

Radical::Radical(unique_ptr<Symbol>& root): AuxOp(root){}

unique_ptr<AuxOp> Radical::copy(){
    unique_ptr<Symbol> copiedRoot = root->copy();
    unique_ptr<AuxOp> copy = make_unique<Radical>(copiedRoot);
    return copy;
}

string Radical::toString(){
    return "";
}
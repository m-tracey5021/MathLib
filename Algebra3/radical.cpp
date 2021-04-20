#include "radical.h"

Radical::Radical(): AuxOp(){}

Radical::Radical(unique_ptr<Symbol>& root): AuxOp(root){}

unique_ptr<AuxOp> Radical::copy(){
    unique_ptr<Symbol> copiedRoot = root->copy();
    unique_ptr<AuxOp> copy = make_unique<Radical>(copiedRoot);
    return copy;
}

string Radical::toString(string target){
    target = '[' + root->toString(false) + "]v" + target;
    unique_ptr<AuxOp>& nextAuxillary = root->getAuxillary();
    if (nextAuxillary != nullptr){
        target = nextAuxillary->toString(target);
    }
    return target;
}
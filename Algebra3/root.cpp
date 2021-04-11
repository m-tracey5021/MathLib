#include "root.h"

Root::Root(): AuxOp(){}

Root::Root(unique_ptr<Symbol>& rootSymbol): AuxOp(rootSymbol){}

unique_ptr<AuxOp> Root::copy(){
    unique_ptr<Symbol> copiedRootSymbol = rootSymbol->copy();
    unique_ptr<AuxOp> copy = make_unique<Root>(copiedRootSymbol);
    return copy;
}

string Root::toString(){
    return "";
}
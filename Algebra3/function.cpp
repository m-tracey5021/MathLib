#include "function.h"

Function::Function(): AuxOp(){}

Function::Function(unique_ptr<Symbol>& rootSymbol): AuxOp(rootSymbol){}

Function::Function(unique_ptr<Symbol>& rootSymbol, unique_ptr<Symbol>& definition): AuxOp(rootSymbol), definition(move(definition)){}

unique_ptr<AuxOp> Function::copy(){
    unique_ptr<Symbol> copiedRootSymbol = rootSymbol->copy();
    unique_ptr<Symbol> copiedDefinition = definition->copy();
    unique_ptr<AuxOp> copy = make_unique<Function>(copiedRootSymbol, copiedDefinition);
    return copy;
}

string Function::toString(){return "";}
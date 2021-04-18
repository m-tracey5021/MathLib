#include "function.h"

Function::Function(): AuxOp(){}

Function::Function(unique_ptr<Symbol>& root): AuxOp(root){}

Function::Function(unique_ptr<Symbol>& root, unique_ptr<Symbol>& definition): AuxOp(root), definition(move(definition)){}

unique_ptr<AuxOp> Function::copy(){
    unique_ptr<Symbol> copiedRoot = root->copy();
    unique_ptr<Symbol> copiedDefinition = definition->copy();
    unique_ptr<AuxOp> copy = make_unique<Function>(copiedRoot, copiedDefinition);
    return copy;
}

string Function::toString(string target){return "";}
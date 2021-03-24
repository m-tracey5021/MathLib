#include "function.h"

Function::Function(): AuxOp(){}

Function::Function(unique_ptr<Symbol>& rootSymbol): AuxOp(rootSymbol){}

Function::Function(unique_ptr<Symbol>& rootSymbol, unique_ptr<Symbol>& definition): AuxOp(rootSymbol), definition(move(definition)){}




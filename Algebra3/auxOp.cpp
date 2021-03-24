#include "auxOp.h"
#include "symbol.h"

AuxOp::AuxOp(){}

AuxOp::AuxOp(unique_ptr<Symbol>& rootSymbol): rootSymbol(move(rootSymbol)){}

AuxOp::~AuxOp() = default;
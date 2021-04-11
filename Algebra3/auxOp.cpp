#include "auxOp.h"
#include "symbol.h"

AuxOp::AuxOp(){}

AuxOp::AuxOp(unique_ptr<Symbol>& rootSymbol): rootSymbol(move(rootSymbol)){}

AuxOp::~AuxOp() = default;

unique_ptr<AuxOp> AuxOp::copy(){}

string AuxOp::toString(){return "";}
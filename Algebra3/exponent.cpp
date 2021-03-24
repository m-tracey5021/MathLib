#include "exponent.h"

Exponent::Exponent(): AuxOp(){}

Exponent::Exponent(unique_ptr<Symbol>& rootSymbol): AuxOp(rootSymbol){}
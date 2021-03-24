#include "root.h"

Root::Root(): AuxOp(){}

Root::Root(unique_ptr<Symbol>& rootSymbol): AuxOp(rootSymbol){}

#include "expression.h"

Expression::Expression(){}

Expression::Expression(unique_ptr<Symbol>& rootSymbol): rootSymbol(move(rootSymbol)){} 
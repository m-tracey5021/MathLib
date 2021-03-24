#include "expressionn.h"

Expressionn::Expressionn(){}

Expressionn::Expressionn(unique_ptr<Symbol>& rootSymbol): rootSymbol(move(rootSymbol)){} 
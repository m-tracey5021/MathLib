#include "variable.h"

Variable::Variable(): Symbol(){}

Variable::Variable(char value): Symbol(value), value(value){}

void Variable::appendChild(unique_ptr<Symbol>& child){}
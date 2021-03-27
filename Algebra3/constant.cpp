#include "constant.h"

Constant::Constant(): Symbol(){}

Constant::Constant(int value): Symbol(value), value(value){}

void Constant::appendChild(unique_ptr<Symbol>& child){}
#include "expression.h"

Constant::Constant(){}

Constant::Constant(bool sign, Expression* root, Expression* exponent, int constant): Expression(sign, root, exponent), constant(constant){}
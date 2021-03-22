#include "exponent.h"

Exponent::Exponent(): AuxOp('^'){}

Exponent::Exponent(ExpressionTree& expression): AuxOp('^', expression){}
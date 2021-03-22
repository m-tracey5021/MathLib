#include "function.h"

Function::Function(): AuxOp('f'){}

Function::Function(ExpressionTree& expression): AuxOp('f', expression){}

Function::Function(ExpressionTree& expression, ExpressionTree& definition): AuxOp('f', expression), definition(move(definition)){}




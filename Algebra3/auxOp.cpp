#include "auxOp.h"

AuxOp::AuxOp(): Symbol(){}

AuxOp::AuxOp(char op): Symbol(op){}

AuxOp::AuxOp(char op, ExpressionTree& expression): Symbol(op), expression(move(expression)){}
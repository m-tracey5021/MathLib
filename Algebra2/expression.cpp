#include "expression.h"

Expression::Expression(): 
                    sign(true), 
                    root(nullptr), 
                    exponent(nullptr), 
                    parentExpression(nullptr){}

Expression::Expression(bool sign, Expression* root, Expression* exponent): 
                    sign(sign), 
                    root(root), 
                    exponent(exponent), 
                    parentExpression(nullptr){}
#include "expression.h"

Expression::Expression(): 
                    sign(true), 
                    root(ExpressionContainer()), 
                    exponent(ExpressionContainer()), 
                    parentExpression(ExpressionContainer()){}

Expression::Expression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent): 
                    sign(sign), 
                    root(root), 
                    exponent(exponent), 
                    parentExpression(ExpressionContainer()){}

Expression::Expression(bool sign, ExpressionContainer&& root, ExpressionContainer&& exponent): 
                    sign(sign), 
                    root(root), 
                    exponent(exponent), 
                    parentExpression(ExpressionContainer()){}

#include "expression.h"

ExpressionContainer::ExpressionContainer(){}

ExpressionContainer::ExpressionContainer(Expression& expression): contained(make_unique<Expression>(expression)){}

void ExpressionContainer::modifyContained(Expression& expression){
    contained = make_unique<Expression>(expression);
}
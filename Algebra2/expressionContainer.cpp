#include "expression.h"

ExpressionContainer::ExpressionContainer(){}

ExpressionContainer::ExpressionContainer(Summation& s): contained(make_unique<Summation>(s.getSign(), s.getRoot(), s.getExponent(), s.getOperands())){}

ExpressionContainer::ExpressionContainer(Multiplication& m): contained(make_unique<Multiplication>(m.getSign(), m.getRoot(), m.getExponent(), m.getOperands())){}

ExpressionContainer::ExpressionContainer(Division& d): contained(make_unique<Division>(d.getSign(), d.getRoot(), d.getExponent(), d.getNumerator(), d.getDenominator())){}

ExpressionContainer::ExpressionContainer(ConstantExpression& ce): contained(make_unique<ConstantExpression>(ce.getSign(), ce.getRoot(), ce.getExponent(), ce.getConstant())){}

ExpressionContainer::ExpressionContainer(VariableExpression& ve): contained(make_unique<VariableExpression>(ve.getSign(), ve.getRoot(), ve.getExponent(), ve.getVariable())){}

void ExpressionContainer::modifyContained(Summation& s){
    contained = make_unique<Summation>(s.getSign(), s.getRoot(), s.getExponent(), s.getOperands());
}

void ExpressionContainer::modifyContained(Multiplication& m){
    contained = make_unique<Multiplication>(m.getSign(), m.getRoot(), m.getExponent(), m.getOperands());
}

void ExpressionContainer::modifyContained(Division& d){
    contained = make_unique<Division>(d.getSign(), d.getRoot(), d.getExponent(), d.getNumerator(), d.getDenominator());
}

void ExpressionContainer::modifyContained(ConstantExpression& ce){
    contained = make_unique<ConstantExpression>(ce.getSign(), ce.getRoot(), ce.getExponent(), ce.getConstant());
}

void ExpressionContainer::modifyContained(VariableExpression& ve){
    contained = make_unique<VariableExpression>(ve.getSign(), ve.getRoot(), ve.getExponent(), ve.getVariable());
}
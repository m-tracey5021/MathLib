#include "expression.h"

VariableExpression::VariableExpression(): Expression(){}

VariableExpression::VariableExpression(bool sign, 
                            ExpressionContainer& root, 
                            ExpressionContainer& exponent, 
                            char variable): 
                            Expression(sign, root, exponent), variable(variable){}

//VariableExpression::VariableExpression(const VariableExpression& v):
//                           Expression(v.sign, ExpressionContainer(v.root), ExpressionContainer(v.exponent)), variable(variable){}

ExpressionContainer VariableExpression::copyExpression(){
    ExpressionContainer copiedRoot = root.copyContainer();
    ExpressionContainer copiedExponent = exponent.copyContainer();
    VariableExpression* copied = new VariableExpression(sign, copiedRoot, copiedExponent, variable);
    return ExpressionContainer(*copied);
}

vector<ExpressionContainer> VariableExpression::getContent(){
    vector<ExpressionContainer> content;
    ExpressionContainer contentContainer = ExpressionContainer(*this);
    content.push_back(contentContainer);
    return content;
}
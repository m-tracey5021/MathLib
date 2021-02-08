#include "expression.h"

ConstantExpression::ConstantExpression(): Expression(){}

ConstantExpression::ConstantExpression(bool sign, 
                        ExpressionContainer& root, 
                        ExpressionContainer& exponent, 
                        int constant): 
                        Expression(sign, root, exponent), constant(constant){}

//ConstantExpression::ConstantExpression(const ConstantExpression& c): 
//                        Expression(c.sign, ExpressionContainer(c.root), ExpressionContainer(c.exponent)), constant(constant){}

ExpressionContainer ConstantExpression::copyExpression(){
    ExpressionContainer copiedRoot = root.copyContainer();
    ExpressionContainer copiedExponent = exponent.copyContainer();
    ConstantExpression* copied = new ConstantExpression(sign, copiedRoot, copiedExponent, constant);
    return ExpressionContainer(*copied);
}

vector<ExpressionContainer> ConstantExpression::getContent(){
    vector<ExpressionContainer> content;
    ExpressionContainer contentContainer = ExpressionContainer(*this);
    content.push_back(contentContainer);
    return content;
}
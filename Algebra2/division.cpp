#include "expression.h"

Division::Division(): Expression(){}

Division::Division(bool sign, 
                        ExpressionContainer& root, 
                        ExpressionContainer& exponent, 
                        ExpressionContainer& numerator,
                        ExpressionContainer& denominator): 
                        Expression(sign, root, exponent), numerator(numerator), denominator(denominator){}

//Division::Division(const Division& d): 
//                        Expression(d.sign, ExpressionContainer(d.root), ExpressionContainer(d.exponent)), numerator(d.numerator), denominator(d.denominator){}

ExpressionContainer Division::copyExpression(){
    ExpressionContainer copiedRoot = root.copyContainer();
    ExpressionContainer copiedExponent = exponent.copyContainer();
    ExpressionContainer copiedNum = numerator.copyContainer();
    ExpressionContainer copiedDenom = denominator.copyContainer();
    Division* copied = new Division(sign, copiedRoot, copiedExponent, copiedNum, copiedDenom);
    return ExpressionContainer(*copied);
}

vector<ExpressionContainer> Division::getContent(){
    vector<ExpressionContainer> content;
    content.push_back(numerator);
    content.push_back(denominator);
    return content;
}
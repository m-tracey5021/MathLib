#include "expression.h"

Summation::Summation(): Expression(){}

Summation::Summation(bool sign, 
                        ExpressionContainer& root, 
                        ExpressionContainer& exponent, 
                        vector<ExpressionContainer>& operands): 
                        Expression(sign, root, exponent), operands(operands){}

//Summation::Summation(const Summation& s):
//                        Expression(s.sign, ExpressionContainer(s.root), ExpressionContainer(s.exponent)), operands(s.operands){}

ExpressionContainer Summation::copyExpression(){
    vector<ExpressionContainer> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        ExpressionContainer ithCopy = operands[i].copyContainer();
        copiedContent.push_back(move(ithCopy));
    }
    ExpressionContainer copiedRoot = root.copyContainer();
    ExpressionContainer copiedExponent = exponent.copyContainer();
    Summation* copied = new Summation(sign, copiedRoot, copiedExponent, copiedContent);
    return ExpressionContainer(*copied);
}

vector<ExpressionContainer> Summation::getContent(){
    return operands;
}
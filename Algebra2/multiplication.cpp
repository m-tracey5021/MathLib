#include "expression.h"

Multiplication::Multiplication(): Expression(){}

Multiplication::Multiplication(bool sign, 
                        ExpressionContainer& root, 
                        ExpressionContainer& exponent, 
                        vector<ExpressionContainer>& operands): 
                        Expression(sign, root, exponent), operands(operands){}

//Multiplication::Multiplication(const Multiplication& m): 
//                        Expression(m.sign, ExpressionContainer(m.root), ExpressionContainer(m.exponent)), operands(m.operands){}

ExpressionContainer Multiplication::copyExpression(){
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

vector<ExpressionContainer> Multiplication::getContent(){
    return operands;
}
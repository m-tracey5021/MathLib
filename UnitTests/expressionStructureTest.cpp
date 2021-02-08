#include "expressionStructureTest.h"
#include "../Algebra2/expression.h"

ExpressionContainer copyConstruct(ExpressionContainer copiedWhenPassed){
    return copiedWhenPassed;
}

bool testCopyConstructor(){
    ExpressionContainer toCopy = ExpressionContainer();
    ExpressionContainer copied = copyConstruct(toCopy);
    if (&toCopy != &copied){
        return true;
    }else{
        return false;
    }
}

bool testDeepCopy(){

    vector<ExpressionContainer> operands;

    ExpressionContainer tmpRoot = ExpressionContainer();
    ExpressionContainer tmpExponent = ExpressionContainer();;
    ConstantExpression constant = ConstantExpression(true, tmpRoot, tmpExponent, 2);
    ExpressionContainer constantContainer = ExpressionContainer(constant);

    tmpRoot = ExpressionContainer();
    tmpExponent = ExpressionContainer();
    VariableExpression variable = VariableExpression(true, tmpRoot, tmpExponent, 'x');
    ExpressionContainer variableContainer = ExpressionContainer(variable);

    tmpRoot = ExpressionContainer();
    tmpExponent = ExpressionContainer();  
    ExpressionContainer* cc = &constantContainer;
    ExpressionContainer* vc = &variableContainer;
    operands.push_back(constantContainer);
    operands.push_back(variableContainer);
    Summation sum = Summation(true, tmpRoot, tmpExponent, operands);
    ExpressionContainer sumContainer = ExpressionContainer(sum);

    ExpressionContainer sumCopy = sumContainer.copy(true);

    if ((&sumCopy != &sumContainer) &
         (&sumCopy.getContent()[0] != &sumContainer.getContent()[0]) &
         (&sumCopy.getContent()[1] != &sumContainer.getContent()[1])){
        return true;
    }else{
        return false;
    }
}
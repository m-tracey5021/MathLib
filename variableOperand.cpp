#include "Trees\EqTrees\variableOperand.h"
#include "Trees\EqTrees\operator.h"

VariableOperand::VariableOperand(){}

VariableOperand::VariableOperand(char var, std::string elementType): TreeElement(elementType){
    variable = var;
}

int* VariableOperand::getValue(){
    return nullptr;
}

char* VariableOperand::getVariable(){
    return &variable;
}

OperatorType* VariableOperand::getType(){
    return nullptr;
}

bool VariableOperand::isParenthesised(){
    return false;
}

std::string VariableOperand::toString(){
    std::string varStr = "";
    varStr.push_back(variable);
    return varStr;
}
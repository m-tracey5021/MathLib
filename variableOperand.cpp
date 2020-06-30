#include "Trees\variableOperand.h"

VariableOperand::VariableOperand(){}

VariableOperand::VariableOperand(char var, std::string elementType): TreeElement(elementType){
    variable = var;
}

char VariableOperand::getVariable(){
    return variable;
}

bool VariableOperand::isParenthesised(){
    return false;
}

bool VariableOperand::isVariable(){
    return true;
}

std::string VariableOperand::toString(){
    std::string varStr = "";
    varStr.push_back(variable);
    return varStr;
}

#include "Trees\EqTrees\staticOperand.h"
#include "Trees\EqTrees\operator.h"
#include <string>

StaticOperand::StaticOperand(){}

StaticOperand::StaticOperand(int val, std::string elementType): TreeElement(elementType){
    value = val;
}

int* StaticOperand::getValue(){
    return &value;
}

char* StaticOperand::getVariable(){
    return nullptr;
}

OperatorType* StaticOperand::getType(){
    return nullptr;
}

bool StaticOperand::isParenthesised(){
    return false;
}

std::string StaticOperand::toString(){
    return std::to_string(value);
}
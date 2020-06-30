
#include "Trees\staticOperand.h"
#include <string>

StaticOperand::StaticOperand(){}

StaticOperand::StaticOperand(int val, std::string elementType): TreeElement(elementType){
    value = val;
}

int StaticOperand::getValue(){
    return value;
}

bool StaticOperand::isParenthesised(){
    return false;
}

bool StaticOperand::isVariable(){
    return false;
}

std::string StaticOperand::toString(){
    return std::to_string(value);
}
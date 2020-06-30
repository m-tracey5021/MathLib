#include "Trees\operator.h"
#include <string>

Operator::Operator(){}

Operator::Operator(OperatorType inputType, bool paren, std::string inputElement): TreeElement(inputElement){
    type = inputType;
    parenthesised = paren;
}

OperatorType Operator::getType(){
    return type;
}

bool Operator::isParenthesised(){
    return parenthesised;
}

bool Operator::isVariable(){
    return false;
}

std::string Operator::toString(){
    if (type == OperatorType::Exponent){
        return "^";
    }else if (type == OperatorType::Division){
        return "/";
    }else if (type == OperatorType::Multiplication){
        return "*";
    }else if (type == OperatorType::Addition){
        return "+";
    }else if (type == OperatorType::Subtraction){
        return "-";
    }else{
        return "=";
    }
}



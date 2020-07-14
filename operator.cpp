#include "Trees\EqTrees\operator.h"
#include <string>

Operator::Operator(){}

Operator::Operator(OperatorType inputType, bool paren, std::string inputElement): TreeElement(inputElement){
    type = inputType;
    parenthesised = paren;
}

int* Operator::getValue(){
    return nullptr;
}

char* Operator::getVariable(){
    return nullptr;
}

OperatorType* Operator::getType(){
    return &type;
}

bool Operator::isParenthesised(){
    return parenthesised;
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



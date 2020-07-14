#include "Trees\treeElement.h"
#include <string>
#include <iostream>

TreeElement::TreeElement(){}

TreeElement::TreeElement(std::string inputElement): elementType(inputElement){}

std::string TreeElement::getElementType(){
     return elementType;
}

int* TreeElement::getValue(){
    return nullptr;
}

char* TreeElement::getVariable(){
    return nullptr;
}

OperatorType* TreeElement::getType(){
    return nullptr;
}

bool TreeElement::isParenthesised(){
     return false;
}

std::string TreeElement::toString(){
     return elementType;
}



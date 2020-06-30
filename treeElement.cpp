#include "Trees\treeElement.h"
#include <string>
#include <iostream>

TreeElement::TreeElement(){}

TreeElement::TreeElement(std::string inputElement): elementType(inputElement){}

std::string TreeElement::getElementType(){
     return elementType;
}

bool TreeElement::isParenthesised(){
     return false;
}

bool TreeElement::isVariable(){
     return false;
}

std::string TreeElement::toString(){
     return elementType;
}



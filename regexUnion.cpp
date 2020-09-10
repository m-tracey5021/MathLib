#include "Regex/regexUnion.h"
#include <string>

RegexUnion::RegexUnion(){}

RegexUnion::RegexUnion(int i, int r, RegexElement* fe, RegexElement* se): RegexElement(i, r), firstElement(fe), secondElement(se){}

RegexElement* RegexUnion::getFirstElement(){
    return firstElement;
}

RegexElement* RegexUnion::getSecondElement(){
    return secondElement;
}

std::string RegexUnion::toString(){
    //std::string retStr = "";
    //retStr.push_back(firstChar);
    //retStr += " U ";
    //retStr.push_back(secondChar);
    std::string retStr = firstElement->toString() + " U " + secondElement->toString();
    return retStr;
}
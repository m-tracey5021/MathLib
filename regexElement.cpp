#include "Regex\regexElement.h"
#include "util.h"

RegexElement::RegexElement(){}

RegexElement::RegexElement(int i, int r): index(i), repititions(r){}

int RegexElement::getIndex(){
    return index;
}

int RegexElement::getRepititions(){
    return repititions;
}

RegexElement* RegexElement::getNext(){
    return next;
}

RegexElement* RegexElement::getPrev(){
    return prev;
}

RegexElement* RegexElement::getChild(){
    return child;
}

RegexElement* RegexElement::getParent(){
    return parent;
}

void RegexElement::setIndex(int i){
    index = i;
}

void RegexElement::setRepititions(int r){
    repititions = r;
}

void RegexElement::setNext(RegexElement* n){
    next = n;
}

void RegexElement::setPrev(RegexElement* p){
    prev = p;
}

void RegexElement::setChild(RegexElement* c){
    child = c;
}

void RegexElement::setParent(RegexElement* p){
    parent = p;
}

std::string RegexElement::toString(){
    //std::string retStr = "RegexElement at index " + std::to_string(index);
    //return retStr;

    return this->toString();
}
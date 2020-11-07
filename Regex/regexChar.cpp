#include "regexChar.h"
#include <string>

RegexChar::RegexChar(){}

RegexChar::RegexChar(int i, int r, char c): RegexElement(i, r), character(c){}

char RegexChar::getCharacter(){
    return character;
}

std::string RegexChar::toString(){
    return std::to_string(character);
}

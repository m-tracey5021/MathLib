#include "Regex\regexString.h"

RegexString::RegexString(){}

RegexString::RegexString(int i, int r, RegexElement* s, int ss): RegexElement(i, r), string(s), stringSize(ss){}

RegexElement* RegexString::getString(){
    return string;
}

int RegexString::getStringSize(){
    return stringSize;
}

std::string RegexString::toString(){
    std::string retStr = "";
    for (int i = 0; i < stringSize; i ++){
        //retStr += string[i].getCharacter();
    }
    return retStr;
}
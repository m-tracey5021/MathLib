#pragma once

#include "regexElement.h"
#include <string>

class RegexChar : public RegexElement{
    private:
        char character;
        //int arrSize;
        //int repititions;
    public:
        RegexChar();
        RegexChar(int i, int r, char c);
        char getCharacter();
        //int getRepititions();
        std::string toString() override;
};
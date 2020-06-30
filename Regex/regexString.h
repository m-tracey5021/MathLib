#pragma once

#include "regexElement.h"
#include "regexChar.h"
#include <string>

class RegexString : public RegexElement{
    private:
        RegexElement* string;
        int stringSize;
    public:
        RegexString();
        RegexString(int i, int r, RegexElement* s, int ss);
        RegexElement* getString();
        int getStringSize();
        std::string toString() override;



};
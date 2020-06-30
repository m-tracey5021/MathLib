#pragma once

#include "regexElement.h"
#include "regexString.h"
#include <string>

class RegexUnion : public RegexElement{
    private:
        RegexElement* firstElement;
        RegexElement* secondElement;
        //int repititions;
    public:
        RegexUnion();
        RegexUnion(int i, int r, RegexElement* fe, RegexElement* se);
        RegexElement* getFirstElement();
        RegexElement* getSecondElement();
        //int getRepititions();
        std::string toString() override;
};
#pragma once

#include "term.h"
#include <string>

using namespace std;

class Expression : Term {
    private:
        Term* terms;
        string nomialType;
    public:
        Expression(){}
        Expression(bool sign, int exponent, Term* terms): Term(sign, exponent), terms(terms){}

};
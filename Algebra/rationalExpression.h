#pragma once

#include "term.h"

class RationalExpression : Term {
    private:
        Term* num;
        Term* denum;
    public:
        RationalExpression(){}
        RationalExpression(int exponent, Term* num, Term* denum): Term(exponent), num(num), denum(denum){}
};
#pragma once

#include "term.h"

class RationalExpression : Term {
    private:
        Term* num;
        Term* denom;
    public:
        RationalExpression(){}
        RationalExpression(bool sign, int exponent, Term* num, Term* denom): Term(sign, exponent), num(num), denom(denom){}
        Term* getNum(){return num;}
        Term* getDenom(){return denom;}
        void setNum(Term* n){num = n;}
        void setDenom(Term* d){denom = d;}
};
#pragma once

#include "term.h"

class ComplexTerm : Term {
    private:
        Term* terms;
    public:
        ComplexTerm(){}
        ComplexTerm(bool sign, int exponent, Term* terms): Term(sign, exponent), terms(terms){}
        
};
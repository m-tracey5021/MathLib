#pragma once

#include "term.h"

class ComplexTerm : Term {
    private:
        Term* terms;
    public:
        ComplexTerm(){}
        ComplexTerm(int exponent, Term* terms): Term(exponent), terms(terms){}
        
};
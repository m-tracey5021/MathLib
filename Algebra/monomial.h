#pragma once

#include "term.h"

class Monomial : Term {
    private:
        Term* terms;
    public:
        Monomial(){}
        Monomial(int exponent, Term* terms): Term(exponent), terms(terms){}
        Term compute(){} // either compute a real number or simplify
};
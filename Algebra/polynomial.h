#pragma once

#include "term.h"
#include "polynomialOperation.h"

class Polynomial : Term {
    private:
        Term* terms;
        PolynomialOperation* operations;
    public:
        Polynomial(){}
        Polynomial(int exponent, Term* terms, PolynomialOperation* operations): Term(exponent), terms(terms), operations(operations){}

};
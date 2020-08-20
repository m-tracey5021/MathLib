#pragma once

#include "term.h"

template<typename t>

class AtomicTerm : Term {
    private:
        t value;
    public:
        AtomicTerm(){}
        AtomicTerm(int exponent, t value): Term(exponent), value(value){}
};
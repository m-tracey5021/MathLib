#pragma once

#include "term.h"

template<typename t>

class AtomicTerm : Term {
    private:
        t value;
    public:
        AtomicTerm(){}
        AtomicTerm(bool sign, int exponent, t value): Term(sign, exponent), value(value){}
        t getValue(){return t;}
        void setValue(t val){value = val;}

};
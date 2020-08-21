#pragma once

#include "term.h"
#include <string>
#include <vector>

using namespace std;

class Expression : Term {
    private:
        string nomialType;
        vector<Term> terms;
    public:
        Expression(){}
        Expression(bool sign, int exponent, vector<Term> terms): Term(sign, exponent), terms(terms){}
        void setTerms(vector<Term> t){terms = t;}
        void appendTerm(Term t){terms.push_back(t);}
};
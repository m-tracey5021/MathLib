#pragma once

#include "term.h"

class RadicalExpression : Term {
    private:
        int root;
        Term* term;
    public:
        RadicalExpression(){}
        RadicalExpression(bool sign, int root, Term* term): Term(sign, 0), root(root), term(term){}
};
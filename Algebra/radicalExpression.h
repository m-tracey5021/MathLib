#pragma once

#include "term.h"

class RadicalExpression : Term {
    private:
        int root;
        Term* term;
    public:
        RadicalExpression(){}
        RadicalExpression(int root, Term* term): Term(0), root(root), term(term){}
};
#pragma once

#include "term.h"

class RadicalExpression : Term {
    private:
        int root;
        Term* term;
    public:
        RadicalExpression(){}
        RadicalExpression(bool sign, int root, Term* term): Term(sign, 0), root(root), term(term){}
        int getRoot(){return root;}
        Term* getTerm(){return term;}
        void setRoot(int r){root = r;}
        void setTerm(Term* t){term = t;}
};
#pragma once

#include "equationComponents.h"

class Equation {
    private:
        TermContainer* left;
        TermContainer* right;
    public:
        Equation(){}
        Equation(TermContainer* left, TermContainer* right): left(left), right(right){}

};
#pragma once

#include "expression.h"

class Equation {
    private:
        Expression* left;
        Expression* right;
    public:
        Equation(){}
        Equation(Expression* left, Expression* right): left(left), right(right){}

};
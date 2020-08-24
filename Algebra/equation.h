#pragma once

#include "equationComponents.h"

class Equation {
    private:
        Polynomial* left;
        Polynomial* right;
    public:
        Equation(){}
        Equation(Polynomial* left, Polynomial* right): left(left), right(right){}

};
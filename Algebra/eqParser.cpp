#include "equation.h"
#include <string>

using namespace std;

Equation stringToEquation(string eqStr){
    /*
    1: initialise pointers 
        1a: initialise two expressions and pointer to current expression to build 
        1b: inititalise pointer to previous term for the purpose of adding exponential information
        1c: initialise current sign
    2: iterate through string
    3: at current char, check whether preceded by a ^

        4: if true - add exponent to previous term
        5: if false - create new atomic term with value of char
            5a: set previous term to newly created atomic term

    6: enter while loop - iterate over characters afer previous term until an operator or a bracket is reached
        6a: check character that has been read
            6ai: on - +, -, / break loop and complete creation of the term, set previous term to newly created complex term
                 and add term to current expression with sign
            6aii: on ^ enter block that adds exponent to term but does not break loop
            6aiii: on (, ), [root] do not break loop but recurse into expression within


    */
}
#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Expression;
class SumOp;
class MulOp;
class DivOp;
class Exponent;
class Radical;
class Variable;
class Constant;

class Symbol {

    public:

        virtual Expression add(SumOp& other) = 0;
        virtual Expression add(MulOp& other) = 0;
        virtual Expression add(DivOp& other) = 0;
        virtual Expression add(Exponent& other) = 0;
        virtual Expression add(Radical& other) = 0;
        virtual Expression add(Variable& other) = 0;
        virtual Expression add(Constant& other) = 0;

        

};




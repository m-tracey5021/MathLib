#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>

using std::string;

using std::vector;

using std::unique_ptr;
using std::make_unique;
using std::move;

using std::optional;
using std::nullopt;

class Expression;
class SumOp;
class MulOp;
class DivOp;
class Exponent;
class Radical;
class Variable;
class Constant;

class Symbol {

    protected:

        char symbol;

        optional<int> value;

    public:

        Symbol(){}

        Symbol(char symbol, optional<int> value): symbol(symbol), value(value){}

        char getSymbol(){ return symbol; }
        
        optional<int> getValue(){ return value; }

        virtual Expression add(SumOp& other) = 0;
        virtual Expression add(MulOp& other) = 0;
        virtual Expression add(DivOp& other) = 0;
        virtual Expression add(Exponent& other) = 0;
        virtual Expression add(Radical& other) = 0;
        virtual Expression add(Variable& other) = 0;
        virtual Expression add(Constant& other) = 0;

        virtual string toString() = 0;

        

};




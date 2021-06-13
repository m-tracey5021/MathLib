#pragma once

#include <string>
#include <vector>
#include <memory>

using std::unique_ptr;
using std::shared_ptr;

class Expression;
class Symbol;
class SumOp;
class MulOp;
class DivOp;
class Constant;
class Variable;
class Exponent;
class Radical;
class Function;

class Visitor {

    public:

        virtual void Visit(SumOp* symbol) = 0;

        virtual void Visit(MulOp* symbol) = 0;

        virtual void Visit(DivOp* symbol) = 0;

        virtual void Visit(Exponent* symbol) = 0;

        virtual void Visit(Radical* symbol) = 0;

        virtual void Visit(Constant* symbol) = 0;

        virtual void Visit(Variable* symbol) = 0;


};
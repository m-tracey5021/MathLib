#pragma once

#include "visitor.h"

class DivideSumOp : public Visitor {

    public:

        SumOp& lhs;

        shared_ptr<Symbol> result;

        DivideSumOp(SumOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class DivideMulOp : public Visitor {

    public:

        MulOp& lhs;

        shared_ptr<Symbol> result;

        DivideMulOp(MulOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class DivideDivOp : public Visitor {

    public:

        DivOp& lhs;

        shared_ptr<Symbol> result;

        DivideDivOp(DivOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class DivideExponent : public Visitor {

    public:

        Exponent& lhs;

        shared_ptr<Symbol> result;

        DivideExponent(Exponent& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class DivideRadical : public Visitor {

    public:

        Radical& lhs;

        shared_ptr<Symbol> result;

        DivideRadical(Radical& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class DivideConstant : public Visitor {

    public:

        Constant& lhs;

        shared_ptr<Symbol> result;

        DivideConstant(Constant& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class DivideVariable : public Visitor {

    public:

        Variable& lhs;

        shared_ptr<Symbol> result;

        DivideVariable(Variable& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};
#pragma once

#include "visitor.h"

class AddToSumOp : public Visitor {

    public:

        SumOp& lhs;

        shared_ptr<Symbol> result;

        AddToSumOp(SumOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class AddToMulOp : public Visitor {

    public:

        MulOp& lhs;

        shared_ptr<Symbol> result;

        AddToMulOp(MulOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class AddToDivOp : public Visitor {

    public:

        DivOp& lhs;

        shared_ptr<Symbol> result;

        AddToDivOp(DivOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class AddToExponent : public Visitor {

    public:

        Exponent& lhs;

        shared_ptr<Symbol> result;

        AddToExponent(Exponent& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class AddToRadical : public Visitor {

    public:

        Radical& lhs;

        shared_ptr<Symbol> result;

        AddToRadical(Radical& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class AddToConstant : public Visitor {

    public:

        Constant& lhs;

        shared_ptr<Symbol> result;

        AddToConstant(Constant& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class AddToVariable : public Visitor {

    public:

        Variable& lhs;

        shared_ptr<Symbol> result;

        AddToVariable(Variable& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};
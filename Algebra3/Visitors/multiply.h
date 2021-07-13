#pragma once

#include "visitor.h"

class MultiplySumOp : public Visitor {

    public:

        SumOp& lhs;

        shared_ptr<Symbol> result;

        MultiplySumOp(SumOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class MultiplyMulOp : public Visitor {

    public:

        MulOp& lhs;

        shared_ptr<Symbol> result;

        MultiplyMulOp(MulOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class MultiplyDivOp : public Visitor {

    public:

        DivOp& lhs;

        shared_ptr<Symbol> result;

        MultiplyDivOp(DivOp& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class MultiplyExponent : public Visitor {

    public:

        Exponent& lhs;

        shared_ptr<Symbol> result;

        MultiplyExponent(Exponent& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class MultiplyRadical : public Visitor {

    public:

        Radical& lhs;

        shared_ptr<Symbol> result;

        MultiplyRadical(Radical& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class MultiplyConstant : public Visitor {

    public:

        Constant& lhs;

        shared_ptr<Symbol> result;

        MultiplyConstant(Constant& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

class MultiplyVariable : public Visitor {

    public:

        Variable& lhs;

        shared_ptr<Symbol> result;

        MultiplyVariable(Variable& lhs);

        void Visit(SumOp* rhs) override;

        void Visit(MulOp* rhs) override;

        void Visit(DivOp* rhs) override;

        void Visit(Exponent* rhs) override;

        void Visit(Radical* rhs) override;

        void Visit(Constant* rhs) override;

        void Visit(Variable* rhs) override;

};

#pragma once

#include "visitor.h"

class AppendToSumOp : public Visitor {

    public:

        SumOp& parent;

        AppendToSumOp(SumOp& parent);

        void Visit(SumOp* child) override;

        void Visit(MulOp* child) override;

        void Visit(DivOp* child) override;

        void Visit(Exponent* child) override;

        void Visit(Radical* child) override;

        void Visit(Constant* child) override;

        void Visit(Variable* child) override;

};

class AppendToMulOp : public Visitor {

    public:

        MulOp& parent;

        AppendToMulOp(MulOp& parent);

        void Visit(SumOp* child) override;

        void Visit(MulOp* child) override;

        void Visit(DivOp* child) override;

        void Visit(Exponent* child) override;

        void Visit(Radical* child) override;

        void Visit(Constant* child) override;

        void Visit(Variable* child) override;

};

class AppendToDivOp : public Visitor {

    public:

        DivOp& parent;

        AppendToDivOp(DivOp& parent);

        void Visit(SumOp* child) override;

        void Visit(MulOp* child) override;

        void Visit(DivOp* child) override;

        void Visit(Exponent* child) override;

        void Visit(Radical* child) override;

        void Visit(Constant* child) override;

        void Visit(Variable* child) override;

};

class AppendToExponent : public Visitor {

    public:

        Exponent& parent;

        AppendToExponent(Exponent& parent);

        void Visit(SumOp* child) override;

        void Visit(MulOp* child) override;

        void Visit(DivOp* child) override;

        void Visit(Exponent* child) override;

        void Visit(Radical* child) override;

        void Visit(Constant* child) override;

        void Visit(Variable* child) override;

};

class AppendToRadical : public Visitor {

    public:

        Radical& parent;

        AppendToRadical(Radical& parent);

        void Visit(SumOp* child) override;

        void Visit(MulOp* child) override;

        void Visit(DivOp* child) override;

        void Visit(Exponent* child) override;

        void Visit(Radical* child) override;

        void Visit(Constant* child) override;

        void Visit(Variable* child) override;

};

class AppendToConstant : public Visitor {

    public:

        Constant& parent;

        AppendToConstant(Constant& parent);

        void Visit(SumOp* child) override;

        void Visit(MulOp* child) override;

        void Visit(DivOp* child) override;

        void Visit(Exponent* child) override;

        void Visit(Radical* child) override;

        void Visit(Constant* child) override;

        void Visit(Variable* child) override;

};

class AppendToVariable : public Visitor {

    public:

        Variable& parent;

        AppendToVariable(Variable& parent);

        void Visit(SumOp* child) override;

        void Visit(MulOp* child) override;

        void Visit(DivOp* child) override;

        void Visit(Exponent* child) override;

        void Visit(Radical* child) override;

        void Visit(Constant* child) override;

        void Visit(Variable* child) override;

};

class Append : public Visitor {

    public:

        // shared_ptr<Symbol> parent;

        shared_ptr<Symbol> child;

        Append(shared_ptr<Symbol> child);

        ~Append();

        void Visit(SumOp* parent) override;

        void Visit(MulOp* parent) override;

        void Visit(DivOp* parent) override;

        void Visit(Exponent* parent) override;

        void Visit(Radical* parent) override;

        void Visit(Constant* parent) override;

        void Visit(Variable* parent) override;

        

};
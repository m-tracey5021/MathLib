#pragma once

#include "visitor.h"

class Append : public Visitor {

    public:

        shared_ptr<Symbol> child;

        Append(shared_ptr<Symbol> child);

        ~Append();

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};

void append(Symbol& parent, shared_ptr<Symbol>& child);

void appendEach(Symbol& parent, shared_ptr<Symbol>& child);
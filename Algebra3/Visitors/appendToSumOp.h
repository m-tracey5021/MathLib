#pragma once

#include "visitor.h"

class AppendToSumOp : public Visitor {

    public:

        Symbol& parent;

        shared_ptr<Symbol> child;

        AppendToSumOp(Symbol& parent, shared_ptr<Symbol> child);

        ~AppendToSumOp();

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

};
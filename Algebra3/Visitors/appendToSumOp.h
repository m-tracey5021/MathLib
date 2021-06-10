#pragma once

#include "append.h"

class AppendToSumOp : public Append {

    public:

        AppendToSumOp(Symbol& parent, shared_ptr<Symbol>& child);

        ~AppendToSumOp();

        Symbol& parent;

        shared_ptr<Symbol>& child;

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

};
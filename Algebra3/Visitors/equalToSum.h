#pragma once

#include "visitor.h"

class EqualToSum : public Visitor {

    public:

        bool isEqual;

        Symbol& compared;

        EqualToSum(Symbol& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};
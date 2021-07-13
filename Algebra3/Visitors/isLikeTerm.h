#pragma once

#include "visitor.h"

class IsLikeTerm : public Visitor {

    public:

        bool isLikeTerm;

        MulOp& compared;

        IsLikeTerm(MulOp& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

};

// class MulIsLikeTerm : public Visitor {

//     public:

//         Symbol& compared;

//         MulIsLikeTerm(Symbol& compared);

//         void Visit(SumOp* symbol) override;

//         void Visit(MulOp* symbol) override;

//         void Visit(DivOp* symbol) override;

//         void Visit(Exponent* symbol) override;

//         void Visit(Radical* symbol) override;

//         void Visit(Constant* symbol) override;

//         void Visit(Variable* symbol) override;

// };

// class DivIsLikeTerm : public Visitor {

//     public:

//         Symbol& compared;

//         DivIsLikeTerm(Symbol& compared);

//         void Visit(SumOp* symbol) override;

//         void Visit(MulOp* symbol) override;

//         void Visit(DivOp* symbol) override;

//         void Visit(Exponent* symbol) override;

//         void Visit(Radical* symbol) override;

//         void Visit(Constant* symbol) override;

//         void Visit(Variable* symbol) override;

// };


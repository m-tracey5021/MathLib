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

class EqualToMul : public Visitor {

    public:

        bool isEqual;

        Symbol& compared;

        EqualToMul(Symbol& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};

class EqualToDiv : public Visitor {

    public:

        bool isEqual;

        Symbol& compared;

        EqualToDiv(Symbol& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};

class EqualToExponent : public Visitor {

    public:

        bool isEqual;

        Symbol& compared;

        EqualToExponent(Symbol& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};

class EqualToRadical : public Visitor {

    public:

        bool isEqual;

        Symbol& compared;

        EqualToRadical(Symbol& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};

class EqualToConstant : public Visitor {

    public:

        bool isEqual;

        Symbol& compared;

        EqualToConstant(Symbol& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};

class EqualToVariable : public Visitor {

    public:

        bool isEqual;

        Symbol& compared;

        EqualToVariable(Symbol& compared);

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        

};


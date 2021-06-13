#pragma once

#include <vector>
#include <utility>
#include "visitor.h"

using std::vector;
using std::pair;

class SanitiseMulOp : public Visitor {

    public:

        vector<int> constants;

        bool multiplyValue;

        shared_ptr<Symbol> other;

        SanitiseMulOp();

        ~SanitiseMulOp();

        void Visit(SumOp* symbol) override;

        void Visit(MulOp* symbol) override;

        void Visit(DivOp* symbol) override;

        void Visit(Exponent* symbol) override;

        void Visit(Radical* symbol) override;

        void Visit(Constant* symbol) override;

        void Visit(Variable* symbol) override;

        void setOther(shared_ptr<Symbol>& other);

};
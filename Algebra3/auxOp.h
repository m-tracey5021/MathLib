#pragma once

#include "symbol.h"
#include "expressionTree.h"

class AuxOp : public Symbol {

    protected:

        ExpressionTree expression;

    public:

        AuxOp();

        AuxOp(char op);

        AuxOp(char op, ExpressionTree& expression);

};
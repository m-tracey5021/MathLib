#pragma once

#include "auxOp.h"

class Function : public AuxOp {
    
    private:

        ExpressionTree definition;

    public:

        Function();

        Function(ExpressionTree& expression);

        Function(ExpressionTree& expression, ExpressionTree& definition);
};
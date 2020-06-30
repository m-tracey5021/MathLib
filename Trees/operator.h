#pragma once

#include "operatorType.h"
#include "treeElement.h"

class Operator : public TreeElement {
    private:
        OperatorType type;
        bool parenthesised;
    public:
        Operator();
        Operator(OperatorType type, bool paren, std::string elementType);
        OperatorType getType();
        bool isParenthesised() override;
        bool isVariable() override;
        std::string toString() override;
};
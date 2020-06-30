#pragma once

#include "treeElement.h"
#include <string>

class VariableOperand : public TreeElement {
    private:
        char variable;
    public:
        VariableOperand();
        VariableOperand(char var, std::string elementType);
        char getVariable();
        bool isParenthesised() override;
        bool isVariable() override;
        std::string toString() override;
};
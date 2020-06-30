#pragma once

#include "treeElement.h"
#include <string>

class StaticOperand : public TreeElement {
    private:
        int value;
    public:
        StaticOperand();
        StaticOperand(int val, std::string elementType);
        int getValue();
        bool isParenthesised() override;
        bool isVariable() override;
        std::string toString() override;
        

};
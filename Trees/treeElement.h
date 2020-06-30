#pragma once

#include <string>

class TreeElement {
    private:
        std::string elementType;
    public:
        TreeElement();
        TreeElement(std::string inputElement);
        std::string getElementType();
        virtual bool isParenthesised();
        virtual bool isVariable();
        virtual std::string toString();
        
};
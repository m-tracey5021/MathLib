#pragma once


#include "EqTrees\operatorType.h"
#include <string>

class TreeElement {
    private:
        std::string elementType;
    public:
        TreeElement();
        TreeElement(std::string inputElement);
        std::string getElementType();
        virtual int* getValue();
        virtual char* getVariable();
        virtual OperatorType* getType();
        virtual bool isParenthesised();
        virtual std::string toString();
        
};
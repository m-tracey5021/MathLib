#pragma once

#include <iostream>
#include <string>

using std::string;

class SymbolContainerBase {

    public:

        SymbolContainerBase(){}

        virtual string toString() = 0;

};

template <typename T>

class SymbolContainer : public SymbolContainerBase {

    public:

        T symbol;

        SymbolContainer(){}

        SymbolContainer(T symbol)
        {
            this->symbol = symbol;
        }

        string toString() override
        {
            std::cout << "to string hit";
            return symbol.toString();
        }
        
};
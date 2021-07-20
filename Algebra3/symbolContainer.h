#pragma once

class SymbolContainerBase {

    public:

        SymbolContainerBase(){}

};

template <typename T>

class SymbolContainer : public SymbolContainerBase {

    public:

        T symbol;

        SymbolContainer(){}

        SymbolContainer(T symbol)
        {
            this.symbol = symbol;
        }
        
};
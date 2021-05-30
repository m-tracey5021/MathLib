#pragma once

#include "symbol.h"

class Constant : public Symbol {

    private:

        int value;

    public:

        Constant();

        Constant(int value);

        Constant(bool sign, int value);

        // Constant(unique_ptr<AuxOp>& auxOp, int value);

        // Constant(bool sign, unique_ptr<AuxOp>& auxOp, int value);

        

        int getValue() override;

        bool isAtomic() override;

        void appendChild(unique_ptr<Symbol>& child) override;

        void removeChild(unique_ptr<Symbol>& child) override;

        void removeChild(int n) override;

        unique_ptr<Symbol>& getChild(int n) override;        

        vector<unique_ptr<Symbol>>& getAllChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren() override;

        vector<unique_ptr<Symbol>> duplicateChildren(int start, int end) override;

        unique_ptr<Symbol> expandExponent() override;

        unique_ptr<Symbol> expandAsExponent(unique_ptr<Symbol>& base) override;

        unique_ptr<Symbol> copy() override;

        string toString() override;

        string toString(int depth, int offset) override;
        
};
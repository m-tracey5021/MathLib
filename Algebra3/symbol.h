#pragma once

#include "auxOp.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>

using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::move;
using std::make_unique;
using std::make_shared;
using std::pair;

class Symbol {

    protected:

        char symbol;

        bool sign;

        unique_ptr<AuxOp> auxOp;

    public:

        Symbol();

        Symbol(char symbol);

        Symbol(char symbol, bool sign);

        Symbol(char symbol, unique_ptr<AuxOp>& auxOp);

        Symbol(char symbol, bool sign, unique_ptr<AuxOp>& auxOp);

        ~Symbol();

        virtual void appendChild(unique_ptr<Symbol>& child) = 0;

        virtual void appendChild(Symbol* child) = 0;

        // virtual unique_ptr<Symbol> getNthChild(int n) = 0;

        // virtual unique_ptr<Symbol> getParent() = 0;

        virtual unique_ptr<Symbol> copy() = 0;

        virtual string toString() = 0;

        

};
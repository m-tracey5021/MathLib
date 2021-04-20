#pragma once

#include "auxOp.h"
// #include "exponent.h"
// #include "radical.h"
// #include "function.h"
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

class Exponent;
class Radical;
class Function;

class Symbol {

    protected:

        char symbol;

        bool sign;

        shared_ptr<Symbol> parent;

        unique_ptr<AuxOp> auxOp;

    public:

        Symbol();

        Symbol(char symbol);

        Symbol(char symbol, bool sign);

        Symbol(char symbol, unique_ptr<AuxOp>& auxOp);

        Symbol(char symbol, bool sign, unique_ptr<AuxOp>& auxOp);

        ~Symbol();

        void setParent(shared_ptr<Symbol>& parent);

        void appendAuxillary(unique_ptr<AuxOp>& auxOp);

        virtual void appendChild(unique_ptr<Symbol>& child) = 0;

        shared_ptr<Symbol>& getParent();

        unique_ptr<AuxOp>& getAuxillary();

        virtual unique_ptr<Symbol>& getNthChild(int n) = 0;

        virtual vector<unique_ptr<Symbol>>& getAllChildren() = 0;

        virtual unique_ptr<Symbol> copy() = 0;

        virtual string toString(bool includeAuxilliaries) = 0;

        

};
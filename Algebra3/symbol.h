#pragma once

#include "auxOp.h"
// #include "exponent.h"
// #include "radical.h"
// #include "function.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <iostream>

using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::move;
using std::make_unique;
using std::make_shared;
using std::pair;

class SumOp;
class MulOp;
class DivOp;
class Constant;
class Variable;
class Exponent;
class Radical;
class Function;

class Symbol {

    protected:

        char symbol;

        bool sign;

        bool isTarget;

        bool isExponent;

        bool isRadical;

        shared_ptr<Symbol> parent;

        // unique_ptr<AuxOp> auxOp;

    public:

        Symbol();

        Symbol(char symbol);

        Symbol(char symbol, bool sign);

        // Symbol(char symbol, unique_ptr<AuxOp>& auxOp);

        // Symbol(char symbol, bool sign, unique_ptr<AuxOp>& auxOp);

        ~Symbol();

        

        // void appendAuxillary(unique_ptr<AuxOp>& auxOp);

        
        char getSymbol();
        
        bool getSign();

        bool getIsTarget();

        bool getIsExponent();

        bool getIsRadical();

        shared_ptr<Symbol>& getParent();


        void setSymbol(char symbol);

        void setSign(bool sign);

        void setAsTarget(bool isTarget);

        void setAsExponent(bool isExponent);

        void setAsRadical(bool isRadical);

        void setParent(shared_ptr<Symbol>& parent);


        virtual int getValue() = 0;

        // unique_ptr<AuxOp>& getAuxillary();

        virtual void appendChild(unique_ptr<Symbol>& child) = 0;

        virtual unique_ptr<Symbol>& getNthChild(int n) = 0;

        virtual vector<unique_ptr<Symbol>>& getAllChildren() = 0;

        virtual vector<unique_ptr<Symbol>> duplicateChildren() = 0;  

        virtual vector<unique_ptr<Symbol>> duplicateChildren(int start, int end) = 0;      

        virtual unique_ptr<Symbol>& expandExponent() = 0;

        virtual unique_ptr<Symbol>& expandAsExponent(unique_ptr<Symbol>& base) = 0;

        virtual unique_ptr<Symbol> copy() = 0;

        virtual string toString() = 0;

        virtual string toString(int depth, int offset) = 0;

        

};
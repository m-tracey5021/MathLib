#pragma once

// #include "auxOp.h"
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

class Expression;
class SumOp;
class MulOp;
class DivOp;
class Constant;
class Variable;
class Exponent;
class Radical;
class Function;

// void addToContext(shared_ptr<Symbol>& symbol, shared_ptr<Expression>& parentExpression);



class Symbol {

    protected:

        char symbol;

        bool sign;

        bool isTarget;

        bool isExponent;

        bool isRadical;

        int index;

        // int indexInContext;

        // shared_ptr<Symbol> parent;

        vector<unique_ptr<Symbol>> children;

        shared_ptr<Expression> parentExpression;

    public:

        Symbol();

        Symbol(char symbol);

        Symbol(char symbol, bool sign);

        Symbol(char symbol, bool sign, vector<unique_ptr<Symbol>>& children);

        Symbol(char symbol, bool sign, shared_ptr<Expression>& parentExpression);

        Symbol(char symbol, bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        ~Symbol();

    

        
        char getSymbol();
        
        bool getSign();

        bool getIsTarget();

        bool getIsExponent();

        bool getIsRadical();

        int getIndex();

        // int getIndexInContext();

        // shared_ptr<Symbol>& getParent();

        // shared_ptr<Symbol>& getParent(int n);

        unique_ptr<Symbol>& getParent();

        shared_ptr<Expression>& getParentExpression();

        void setSymbol(char symbol);

        void setSign(bool sign);

        void setIsTarget(bool isTarget);

        void setIsExponent(bool isExponent);

        void setIsRadical(bool isRadical);

        void setIndex(int index);

        // void setIndexInContext(int index);

        // void setParent(shared_ptr<Symbol>& parent);

        void setParentExpression(shared_ptr<Expression>& parentExpression);


        virtual int getValue() = 0;

        virtual bool isAtomic() = 0;

        virtual bool isAtomicExponent() = 0;

        virtual bool isAtomicNumerator() = 0;

        // virtual bool isParentTo(Symbol* symbol) = 0;

        // virtual unique_ptr<Symbol>& searchParent(Symbol* symbol, unique_ptr<Symbol>& parent) = 0;

        virtual void setChildren(vector<unique_ptr<Symbol>>& children) = 0;

        virtual void appendChild(unique_ptr<Symbol>& child) = 0;
        // virtual void appendChild(unique_ptr<SumOp> child) = 0;
        // virtual void appendChild(unique_ptr<MulOp> child) = 0;
        // virtual void appendChild(unique_ptr<DivOp> child) = 0;
        // virtual void appendChild(unique_ptr<Constant> child) = 0;
        // virtual void appendChild(unique_ptr<Variable> child) = 0;

        virtual void appendChildren(vector<unique_ptr<Symbol>>& children) = 0;

        virtual void appendChildren(vector<unique_ptr<Symbol>>& children, int n) = 0;

        virtual void replaceChild(unique_ptr<Symbol>& child, int n) = 0;
        virtual void replaceChild(unique_ptr<SumOp>& child, int n) = 0;
        virtual void replaceChild(unique_ptr<MulOp>& child, int n) = 0;

        virtual void removeChild(unique_ptr<Symbol>& child) = 0;

        virtual void removeChild(int n) = 0;

        

        

        

        virtual unique_ptr<Symbol>& getChild(int n) = 0;

        virtual vector<unique_ptr<Symbol>>& getChildren() = 0;

        virtual vector<unique_ptr<Symbol>> duplicateChildren() = 0;  

        virtual vector<unique_ptr<Symbol>> duplicateChildren(int start, int end) = 0;      

        virtual void expandExponent(Symbol* parent) = 0;

        virtual void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) = 0;

        virtual unique_ptr<Symbol> copy() = 0;

        virtual string toString(bool hasParent) = 0;

        virtual string toString(int depth, int offset) = 0;

        

};


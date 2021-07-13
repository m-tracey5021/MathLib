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
#include <variant>
#include <optional>
#include "Visitors/visitor.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::move;
using std::make_unique;
using std::make_shared;
using std::pair;
using std::variant;
using std::optional;
using std::nullopt;

class Expression;
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

        int index;

        vector<int> path;

        shared_ptr<Symbol> parent;

        vector<shared_ptr<Symbol>> children;

        shared_ptr<Expression> parentExpression;

    public:

        Symbol();

        Symbol(char symbol);

        Symbol(char symbol, bool sign);

        Symbol(char symbol, bool sign, vector<shared_ptr<Symbol>>& children);

        Symbol(char symbol, bool sign, shared_ptr<Expression>& parentExpression);

        Symbol(char symbol, bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression);

        ~Symbol();

    

        
        char getSymbol();
        
        bool getSign();

        bool getIsTarget();

        bool getIsExponent();

        bool getIsRadical();

        int getIndex();

        vector<int> getPath();

        int getPathValue();

        shared_ptr<Symbol> getParent();

        shared_ptr<Symbol> getWrapped();

        vector<shared_ptr<Symbol>>& getChildren();

        shared_ptr<Expression> getParentExpression();

        optional<shared_ptr<Symbol>> getNode(Symbol* target);

        void setSymbol(char symbol);

        void setSign(bool sign);

        void setIsTarget(bool isTarget);

        void setIsExponent(bool isExponent);

        void setIsRadical(bool isRadical);

        void setIndex(int index);

        void setPath(vector<int> path);

        void setPathValue(int value);

        void setParent(shared_ptr<Symbol> parent);

        void setParentExpression(shared_ptr<Expression> parentExpression);

        void testVariant(variant<shared_ptr<SumOp>, shared_ptr<MulOp>, shared_ptr<DivOp>> symbols);

        
        virtual void accept(Visitor* visitor) = 0;

        virtual optional<int> getValue() = 0;

        virtual bool isAtomic() = 0;

        virtual bool isAtomicExponent() = 0;

        virtual bool isAtomicNumerator() = 0; 

        virtual bool isEqual(Symbol* other) = 0;   

        virtual bool isLikeTerm(Symbol* other) = 0;

        virtual void appendChild(shared_ptr<Symbol>& child) = 0;

        virtual void setChildren(vector<shared_ptr<Symbol>>& children) = 0;

        virtual void appendChildren(vector<shared_ptr<Symbol>>& children) = 0;

        virtual void appendChildren(vector<shared_ptr<Symbol>>& children, int n) = 0;

        virtual void replaceChild(shared_ptr<Symbol>& child, int n) = 0;

        virtual void removeChild(shared_ptr<Symbol>& child) = 0;

        virtual void removeChild(int n) = 0;

        virtual vector<shared_ptr<Symbol>> duplicateChildren() = 0;  

        virtual vector<shared_ptr<Symbol>> duplicateChildren(int start, int end) = 0; 

        virtual void evaluateConstants() = 0; 

        virtual void expandExponent(Symbol* parent) = 0;

        virtual void expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent) = 0;

        virtual void sumLikeTerms() = 0;

        virtual shared_ptr<Symbol> copy() = 0;

        virtual shared_ptr<Symbol> sanitise() = 0;

        virtual string toString(bool hasParent) = 0;

        virtual string toString(int depth, int offset) = 0;

        

};




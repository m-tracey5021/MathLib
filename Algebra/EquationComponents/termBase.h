#pragma once

#include <string>
#include <vector>

using namespace std;

class TermBase {
    protected:
        bool sign;
        TermBase* root;
        TermBase* exponent;
        TermBase* parentExpression;
        string expressionString;
    public:
        TermBase(): sign(1), root(nullptr), exponent(nullptr), parentExpression(nullptr){}
        TermBase(bool sign, TermBase* root, TermBase* exponent): sign(sign), root(root), exponent(exponent), parentExpression(nullptr){}

        bool getSign(){return sign;}
        TermBase* getRoot(){return root;}
        TermBase* getExponent(){return exponent;}
        TermBase* getParentExpression(){return parentExpression;}
        string getExpressionString(){return expressionString;}

        void setSign(bool s){sign = s; updateExpressionString();}
        void setRoot(TermBase* r){root = r; updateExpressionString();}
        void setExponent(TermBase* e){exponent = e; updateExpressionString();}
        void setParentExpression(TermBase* p){parentExpression = p;}
        void updateExpressionString(){expressionString = this->toString();}
        bool isEqual(TermBase* other){if (expressionString == other->getExpressionString()){return true;}else{return false;}}

        // methods to override

        virtual void appendTerm(TermBase* t){}
        virtual void removeTerm(int index){}

        //virtual TermBase* getCoefficient(){return nullptr;}
        //virtual void setCoefficient(TermBase* c){}

        virtual bool isOne(){return false;}
        virtual bool isAtomic(){return false;}
        virtual bool isLikeTerm(TermBase* other){return false;}

        virtual TermBase* sum(TermBase* other){return nullptr;}
        virtual TermBase* multiply(TermBase* other){return nullptr;}
        virtual TermBase* divide(TermBase* other){return nullptr;}

        virtual TermBase* factor(){return nullptr;}
        virtual vector<TermBase*> allFactors(){vector<TermBase*> dummy; return dummy;}

        virtual TermBase* copy(){return nullptr;}
        virtual string toString(){return "term base";}
    
};
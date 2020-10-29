#pragma once

#include <string>
#include <vector>

enum class OperationType{
    Summation,
    Multiplication,
    Division
};

class TermBase {
    protected:
        bool sign;
        TermBase* root;
        TermBase* exponent;
        TermBase* parentExpression;
        std::string expressionString;
    public:
        TermBase(): sign(1), root(nullptr), exponent(nullptr), parentExpression(nullptr){}

        TermBase(bool sign, TermBase* root, TermBase* exponent): sign(sign), root(root), exponent(exponent), parentExpression(nullptr){}

        bool getSign(){return sign;}

        TermBase* getRoot(){return root;}

        TermBase* getExponent(){return exponent;}

        TermBase* getParentExpression(){return parentExpression;}

        std::string getExpressionString(){return expressionString;}

        void setSign(bool s){sign = s; updateExpressionString();}

        void setRoot(TermBase* r){root = r; updateExpressionString();}

        void setExponent(TermBase* e){exponent = e; updateExpressionString();}

        void setParentExpression(TermBase* p){parentExpression = p;}

        void updateExpressionString(){expressionString = this->toString();}
        
        bool isEqual(TermBase* other){if (expressionString == other->getExpressionString()){return true;}else{return false;}}

        // virtual

        virtual void appendTerm(TermBase* t){}

        virtual void removeTerm(int index){}

        // pure virtual

        virtual bool isOne() = 0;

        virtual bool isAtomic() = 0;

        virtual bool isLikeTerm(TermBase* other) = 0;

        virtual TermBase* sum(TermBase* other) = 0;

        virtual TermBase* multiply(TermBase* other) = 0;

        virtual TermBase* divide(TermBase* other) = 0;

        virtual TermBase* factor() = 0;

        virtual std::vector<TermBase*> allFactors() = 0;

        //virtual TermBase* copy() = 0;

        virtual std::string toString() = 0;

    
};

class Constant : public TermBase {
    private:
        int constant;
    public:
        Constant();

        Constant(bool sign, TermBase* root, TermBase* exponent, int constant);

        ~Constant();

        int getConstant(){return constant;}

        void setConstant(int c){constant = c; updateExpressionString();}

        bool isOne() override;

        bool isAtomic() override;

        bool isLikeTerm(TermBase* other) override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* factor() override;

        std::vector<TermBase*> allFactors() override;

        std::string toString() override;
};

class Variable : public TermBase {
    private:
        char variable;
    public:
        Variable();
        
        Variable(bool sign, TermBase* root, TermBase* exponent, char variable);

        ~Variable();

        char getVariable(){return variable;}

        void setVariable(char v){variable = v; updateExpressionString();}

        bool isOne() override;

        bool isAtomic() override;

        bool isLikeTerm(TermBase* other) override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* factor() override;

        std::vector<TermBase*> allFactors() override;

        std::string toString() override;

};

class TermContainer : public TermBase {
    private:
        std::vector<TermBase*> terms;
        OperationType operationType;
        Constant* coefficient;
    public:
        TermContainer();

        TermContainer(bool sign, TermBase* root, TermBase* exponent, Constant* coefficient);

        ~TermContainer();

        std::vector<TermBase*> getTerms();

        OperationType getOperationType();

        Constant* getCoefficient();

        void setTerms(std::vector<TermBase*> t);

        void setOperationType(OperationType o);

        void setCoefficient(Constant* c);

        void appendTerm(TermBase* t) override;

        void removeTerm(int i) override;
        
        bool isOne() override;

        bool isAtomic() override;

        bool isLikeTerm(TermBase* other) override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* factor() override;

        std::vector<TermBase*> allFactors() override;

        std::string toString() override;
};
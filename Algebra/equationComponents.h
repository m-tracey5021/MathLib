#pragma once

#include <utility>
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
        TermBase();

        TermBase(bool sign, TermBase* root, TermBase* exponent);

        bool getSign();

        TermBase* getRoot();

        TermBase* getExponent();

        TermBase* getParentExpression();

        std::string getExpressionString();

        void setSign(bool s);

        void setRoot(TermBase* r);

        void setExponent(TermBase* e);

        void setParentExpression(TermBase* p);

        void updateExpressionString();
        
        bool isEqual(TermBase* other);

        // virtual

        virtual void appendTerm(TermBase* t){}

        virtual void removeTerm(int index){}

        // pure virtual

        virtual bool isOne() = 0;

        virtual bool isAtomic() = 0;

        virtual bool isAtomicExponent() = 0;

        virtual bool isAtomicNumerator() = 0;

        virtual bool isLikeTerm(TermBase* other) = 0;

        virtual TermBase* sum(TermBase* other) = 0;

        virtual TermBase* multiply(TermBase* other) = 0;

        virtual TermBase* divide(TermBase* other) = 0;

        virtual TermBase* expandExponent(TermBase* term) = 0;

        virtual TermBase* factor() = 0;

        virtual std::vector<TermBase*> allFactors() = 0;

        virtual TermBase* copy() = 0;

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

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeTerm(TermBase* other) override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* expandExponent(TermBase* term) override;

        TermBase* factor() override;

        std::vector<TermBase*> allFactors() override;

        TermBase* copy() override;

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

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeTerm(TermBase* other) override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* expandExponent(TermBase* term) override;

        TermBase* factor() override;

        std::vector<TermBase*> allFactors() override;

        TermBase* copy() override;

        std::string toString() override;

};

class TermContainer : public TermBase {
    private:
        Constant* coefficient;
        OperationType operationType;
        std::vector<TermBase*> terms;
        
        
    public:
        TermContainer();

        TermContainer(bool sign, TermBase* root, TermBase* exponent, Constant* coefficient);

        TermContainer(bool sign, TermBase* root, TermBase* exponent, Constant* coefficient, OperationType operationType, std::vector<TermBase*> terms);

        ~TermContainer();

        Constant* getCoefficient();

        OperationType getOperationType();

        std::vector<TermBase*> getTerms();   

        void setCoefficient(Constant* c);  

        void setOperationType(OperationType o);   

        void setTerms(std::vector<TermBase*> t);

        void appendTerm(TermBase* t) override;

        void removeTerm(int i) override;
        
        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeTerm(TermBase* other) override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* expandExponent(TermBase* term) override;

        TermBase* factor() override;

        std::vector<TermBase*> allFactors() override;

        TermBase* copy() override;

        std::string toString() override;
};
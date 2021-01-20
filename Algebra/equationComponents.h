#pragma once

#include <utility>
#include <string>
#include <vector>

class TermBase;
class Constant;
class Variable;
class TermContainer;

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

        bool friend operator==(TermBase* first, TermBase* second){return first->isEqual(second);}

        bool isIn(std::vector<TermBase*> terms);

        void getAllSubTerms(std::vector<TermBase*>& terms,
                                std::vector<TermBase*>& subTerms,
                                int start,
                                int end);

        // === Virtual ===

        virtual void appendTerm(TermBase* t){}

        virtual void removeTerm(int i){}

        virtual void replaceTerm(int i, TermBase* t){}

        // Comparison Overloads

        // virtual bool operator==(Constant* other);
        // virtual bool operator==(Variable* other);
        // virtual bool operator==(TermContainer* other);

        //  === Pure Virtual ===
        
        // Operator Overloads

        virtual TermBase* operator+(TermBase* other) = 0;
        
        virtual TermBase* operator-(TermBase* other) = 0;

        virtual TermBase* operator*(TermBase* other) = 0;

        virtual TermBase* operator/(TermBase* other) = 0;

        // Clean

        virtual void sanitiseForFactoring() = 0;

        // Test

        virtual bool isOne() = 0;

        virtual bool isAtomic() = 0;

        virtual bool isAtomicExponent() = 0;

        virtual bool isAtomicNumerator() = 0;

        virtual bool isLikeTerm(TermBase* other) = 0;

        virtual bool isMergeable() = 0;

        // Get 

        virtual int* getValue() = 0;

        virtual TermBase* getAtom() = 0;

        virtual std::vector<TermBase*> getContent() = 0;

        // Manipulate

        virtual TermBase* sum(TermBase* other) = 0;

        virtual TermBase* multiply(TermBase* other) = 0;

        virtual TermBase* divide(TermBase* other) = 0;

        virtual TermBase* mergeMultiplications(TermBase* other) = 0;

        //virtual TermBase* expandConstant() = 0;

        virtual TermBase* expandForExponent() = 0;

        virtual TermBase* expandAsExponent(TermBase* baseTerm) = 0;

        virtual TermBase* expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational) = 0;

        virtual TermBase* expandAsNegativeExponent(TermBase* baseTerm) = 0;

        virtual TermBase* factor() = 0;

        virtual std::vector<TermBase*> getConstantFactors() = 0;

        virtual std::vector<TermBase*> getAllFactors() = 0;

        // Misc functions

        virtual TermBase* copy() = 0;

        virtual std::string toString() = 0;

        virtual std::string exponentToString() = 0;

    
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

        // ===

        bool operator==(Constant* other) override;
        bool operator==(Variable* other) override;
        bool operator==(TermContainer* other) override;

        TermBase* operator+(TermBase* other) override;
        
        TermBase* operator-(TermBase* other) override;

        TermBase* operator*(TermBase* other) override;

        TermBase* operator/(TermBase* other) override;

        void sanitiseForFactoring() override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeTerm(TermBase* other) override;

        bool isMergeable() override;

        int* getValue() override;

        TermBase* getAtom() override;

        std::vector<TermBase*> getContent() override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* mergeMultiplications(TermBase* other) override;
        
        //TermBase* expandConstant() override;

        TermBase* expandForExponent() override;

        TermBase* expandAsExponent(TermBase* baseTerm) override;

        TermBase* expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational) override;

        TermBase* expandAsNegativeExponent(TermBase* baseTerm) override;

        TermBase* factor() override;

        std::vector<TermBase*> getConstantFactors() override;

        std::vector<TermBase*> getAllFactors() override;

        TermBase* copy() override;

        std::string toString() override;

        std::string exponentToString() override;
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

        // ===

        bool operator==(Constant* other) override;
        bool operator==(Variable* other) override;
        bool operator==(TermContainer* other) override;

        TermBase* operator+(TermBase* other) override;
        
        TermBase* operator-(TermBase* other) override;

        TermBase* operator*(TermBase* other) override;

        TermBase* operator/(TermBase* other) override;

        void sanitiseForFactoring() override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeTerm(TermBase* other) override;

        bool isMergeable() override;

        int* getValue() override;

        TermBase* getAtom() override;

        std::vector<TermBase*> getContent() override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* mergeMultiplications(TermBase* other) override;
        
        //TermBase* expandConstant() override;

        TermBase* expandForExponent() override;

        TermBase* expandAsExponent(TermBase* baseTerm) override;

        TermBase* expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational) override;

        TermBase* expandAsNegativeExponent(TermBase* baseTerm) override;

        TermBase* factor() override;

        std::vector<TermBase*> getConstantFactors() override;

        std::vector<TermBase*> getAllFactors() override;

        TermBase* copy() override;

        std::string toString() override;

        std::string exponentToString() override;

};

class TermContainer : public TermBase {
    private:
        //Constant* coefficient;
        OperationType operationType;
        std::vector<TermBase*> terms;
        
        
    public:
        TermContainer();

        TermContainer(bool sign, TermBase* root, TermBase* exponent);

        TermContainer(bool sign, TermBase* root, TermBase* exponent, OperationType operationType, std::vector<TermBase*> terms);

        ~TermContainer();

        //Constant* getCoefficient();

        OperationType getOperationType();

        std::vector<TermBase*> getTerms();  

        std::vector<TermBase*> duplicateTerms(int start, int end);

        //void setCoefficient(Constant* c);  

        void setOperationType(OperationType o);   

        void setTerms(std::vector<TermBase*> t);

        // ===

        void appendTerm(TermBase* t) override;

        void removeTerm(int i) override;

        void replaceTerm(int i, TermBase* t) override;

        bool operator==(Constant* other) override;
        bool operator==(Variable* other) override;
        bool operator==(TermContainer* other) override;

        TermBase* operator+(TermBase* other) override;
        
        TermBase* operator-(TermBase* other) override;

        TermBase* operator*(TermBase* other) override;

        TermBase* operator/(TermBase* other) override;

        void sanitiseForFactoring() override;
        
        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeTerm(TermBase* other) override;

        bool isMergeable() override;

        int* getValue() override;

        TermBase* getAtom() override;

        std::vector<TermBase*> getContent() override;

        TermBase* sum(TermBase* other) override;

        TermBase* multiply(TermBase* other) override;

        TermBase* divide(TermBase* other) override;

        TermBase* mergeMultiplications(TermBase* other) override;

        //TermBase* expandConstant() override;

        TermBase* expandForExponent() override;

        TermBase* expandAsExponent(TermBase* baseTerm) override;

        TermBase* expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational) override;

        TermBase* expandAsNegativeExponent(TermBase* baseTerm) override;

        TermBase* factor() override;

        std::vector<TermBase*> getConstantFactors() override;

        std::vector<TermBase*> getAllFactors() override;

        TermBase* copy() override;

        std::string toString() override;

        std::string exponentToString() override;
};
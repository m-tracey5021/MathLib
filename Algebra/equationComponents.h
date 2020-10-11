#pragma once

#include <string>
#include <vector>

using namespace std;

enum class OperationType{
    Summation,
    Multiplication,
    Division
};

class TermBase {
    protected:
        bool sign;
        int coefficient;
        TermBase* exponent;
        TermBase* parentExpression;
        string representation;
    public:
        TermBase(): sign(1), coefficient(1), exponent(nullptr), parentExpression(nullptr){}
        TermBase(bool sign, int coefficient, TermBase* exponent): sign(sign), coefficient(coefficient), exponent(exponent), parentExpression(nullptr){}
        bool getSign(){return sign;}
        int getCoefficient(){return coefficient;}
        TermBase* getExponent(){return exponent;}
        TermBase* getParentExpression(){return parentExpression;}
        string getRepresentation(){return representation;}
        void setSign(bool s){sign = s;}
        void setCoefficient(int c){coefficient = c;}
        void setExponent(TermBase* e){exponent = e;}
        void setParentExpression(TermBase* p){parentExpression = p;}
        void updateRepresentation(){representation = this->toString();}
        bool isEqual(TermBase* other){if (representation == other->getRepresentation()){return true;}else{return false;}}

        // methods to override

        virtual void appendTerm(TermBase* t){}
        virtual void removeTerm(TermBase* t){}
        virtual void removeTerm(int index){}
        virtual bool isOne(){return false;}
        virtual bool isSimpleNumeric(){return false;}
        virtual bool isSummable(TermBase* other){return false;}
        virtual vector<TermBase*> allFactors(){vector<TermBase*> dummy; return dummy;}
        virtual TermBase* factorTerm(bool high){return nullptr;}
        virtual TermBase* compute(){return nullptr;} // either compute lowest term or real number
        virtual string toString(){return "term base";}
    
};

class Variable : public TermBase {
    private:
        char variable;
    public:
        Variable(): TermBase(){}
        Variable(bool sign, int coefficient, TermBase* exponent, char variable): TermBase(sign, coefficient, exponent), variable(variable){}
        string toString() override {
            string termStr = "";
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    string totalTerm = variable + "^(" + exponent->toString() + ')';
                }
            }else{
                return termStr + variable;
            }
        }

};

class TermContainer : public TermBase {
    private:
        vector<TermBase*> terms;
        OperationType operationType;
    public:
        TermContainer(): TermBase(){}
        TermContainer(bool sign, int coefficient, TermBase* exponenet): TermBase(sign, coefficient, exponenet){}
        vector<TermBase*> getTerms(){return terms;}
        OperationType getOperationType(){return operationType;}
        void setTerms(vector<TermBase*> t){terms = t;}
        void setOperationType(OperationType o){operationType = o;}
};


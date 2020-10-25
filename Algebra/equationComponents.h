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
        virtual vector<TermBase*> allFactors(){vector<TermBase*> dummy; return dummy;}
        virtual TermBase* factorTerm(bool high){return nullptr;}

        virtual string toString(){return "term base";}
    
};

class Constant : public TermBase {
    private:
        int constant;
    public:
        Constant(): TermBase(){}
        Constant(bool sign, TermBase* root, TermBase* exponent, int constant): TermBase(sign, root, exponent), constant(constant){updateExpressionString();}

        int getConstant(){return constant;}
        void setConstant(int c){constant = c; updateExpressionString();}

        bool isOne() override {
            if (constant == 1){
                return true;
            }else{
                return false;
            }
        }
        bool isAtomic() override {return true;}
        bool isLikeTerm(TermBase* other) override {
            if (!other->isAtomic()){
                return false;
            }else{
                Constant* constant = dynamic_cast<Constant*> (other);
                Variable* variable = dynamic_cast<Variable*> (other);
                if (constant){
                    return true;
                }
                if (variable){
                    return false;
                }
            }
        }

        string toString() override {
            string termStr = "";
            if (!sign){
                termStr += '-';
            }

            termStr += to_string(constant);

            if (root != nullptr){
                if (!root->isOne()){
                    termStr = '[' + root->toString() + '|' + termStr + ']';
                }
            }
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    if (exponent->getSign()){
                        termStr = termStr + "^(" + exponent->toString() + ')';
                    }else{
                        termStr = termStr + "^" + exponent->toString();
                    }
                }
            }

            return termStr;
        }
};

class Variable : public TermBase {
    private:
        char variable;
    public:
        Variable(): TermBase(){}
        Variable(bool sign, TermBase* root, TermBase* exponent, char variable): TermBase(sign, root, exponent), variable(variable){updateExpressionString();}

        char getVariable(){return variable;}
        void setVariable(char v){variable = v; updateExpressionString();}

        bool isOne() override {return false;}
        bool isAtomic() override {return true;}
        bool isLikeTerm(TermBase* other) override {
            if (!other->isAtomic()){
                return false;
            }else{
                Constant* constant = dynamic_cast<Constant*> (other);
                Variable* variable = dynamic_cast<Variable*> (other);
                if (constant){
                    return false;
                }
                if (variable){
                    return true;
                }
            }
        }

        string toString() override {
            string termStr = "";
            if (!sign){
                termStr += '-';
            }

            termStr += variable;

            if (root != nullptr){
                if (!root->isOne()){
                    termStr = '[' + root->toString() + '|' + termStr + ']';
                }
            }
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    if (exponent->getSign()){
                        termStr = termStr + "^(" + exponent->toString() + ')';
                    }else{
                        termStr = termStr + "^" + exponent->toString();
                    }
                    
                }
            }

            return termStr;
        }

};

class TermContainer : public TermBase {
    private:
        vector<TermBase*> terms;
        OperationType operationType;
        Constant* coefficient;
    public:
        TermContainer(): TermBase(){
            coefficient = new Constant(true, nullptr, nullptr, 1);
            updateExpressionString();
        }
        TermContainer(bool sign, TermBase* root, TermBase* exponent, Constant* coefficient): TermBase(sign, root, exponent), coefficient(coefficient){
            updateExpressionString();
        }

        vector<TermBase*> getTerms(){return terms;}
        OperationType getOperationType(){return operationType;}
        void setTerms(vector<TermBase*> t){terms = t; updateExpressionString();}
        void setOperationType(OperationType o){operationType = o; updateExpressionString();}

        void appendTerm(TermBase* t) override {terms.push_back(t); t->setParentExpression(this); updateExpressionString();}
        void removeTerm(int i) override {terms.erase(terms.begin() + i); updateExpressionString();}
        Constant* getCoefficient(){return coefficient;}
        void setCoefficient(Constant* c){coefficient = c; updateExpressionString();}
        bool isOne() override {
            if (terms.size() == 1 & terms[0]->isOne()){
                return true;
            }else{
                return false;
            }
        }
        bool isAtomic() override {
            if (terms.size() == 1 & terms[0]->isAtomic()){
                return true;
            }else{
                return false;
            }
        }
        bool isLikeTerm(TermBase* other) override {
            TermContainer* otherContainer = dynamic_cast<TermContainer*> (other);

            if (otherContainer){
                if (operationType != otherContainer->getOperationType()){
                    return false;
                }else{
                    if (operationType == OperationType::Multiplication){ // only need to check one operationType because we know both are the same if this if-block is entered
                        int indexThis;
                        int indexOther;

                        coefficient->isOne() ? indexThis = 0 : indexThis = 1;
                        otherContainer->getCoefficient()->isOne() ? indexOther = 0: indexOther = 1;
                        
                        if (terms.size() - indexThis != otherContainer->getTerms().size() - indexOther){ // if the two terms are different sizes, they cant be added
                            return false;
                        }else{
                            bool termsEqual = true;
                            while (termsEqual){
                                if (!terms[indexThis]->isEqual(otherContainer->getTerms()[indexOther])){
                                    termsEqual = false;
                                }
                                indexThis ++;
                                indexOther ++;
                            }
                            return termsEqual; // return true if all components are the same, flase if else
                        }
                        
                        
                    }else if (operationType == OperationType::Division){

                    }else{

                    }
                }
            }else{
                return false;
            }
            
        }
        string toString() override {
            string termStr = "";
            if (operationType == OperationType::Multiplication){
                for (int i = 0; i < terms.size(); i ++){
                    termStr += terms[i]->toString();
                }
                if (!sign){
                    termStr = '-' + termStr;
                }
            }else if (operationType == OperationType::Division){
                for (int i = 0; i < terms.size(); i ++){
                    if (i == terms.size() - 1){
                        termStr += terms[i]->toString();
                    }else{
                        termStr += terms[i]->toString() + '/';
                    }
                    
                }
                if (!sign){
                    termStr = "-{" + termStr + '}';
                }else{
                    termStr = '{' + termStr + '}';
                }
            }else{
                for (int i = 0; i < terms.size(); i ++){
                    if (i == 0){
                        termStr += terms[i]->toString();
                    }else{
                        if (terms[i]->getSign()){
                            termStr += '+' + terms[i]->toString();
                        }else{
                            termStr += '-' + terms[i]->toString();
                        }
                    }
                }
                if (!sign){
                    termStr = "-(" + termStr + ')';
                }else{
                    if (terms.size() != 1 & parentExpression != nullptr){
                        termStr = '(' + termStr + ')';
                    }
                }
            }

            if (root != nullptr){
                if (!root->isOne()){
                    termStr = '[' + root->toString() + '|' + termStr + ']';
                }
            }
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    if (exponent->getSign()){
                        termStr = termStr + "^(" + exponent->toString() + ')';
                    }else{
                        termStr = termStr + '^' + exponent->toString();
                        
                    }
                }
            }


            return termStr;
        }
};


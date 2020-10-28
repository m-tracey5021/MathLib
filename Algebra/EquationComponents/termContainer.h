#pragma once

#include <string>
#include <vector>
#include "termBase.h"


using namespace std;

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
        Constant* getCoefficient(){return coefficient;}
        void setTerms(vector<TermBase*> t){terms = t; updateExpressionString();}
        void setOperationType(OperationType o){operationType = o; updateExpressionString();}
        void setCoefficient(Constant* c){coefficient = c; updateExpressionString();}

        void appendTerm(TermBase* t) override {terms.push_back(t); t->setParentExpression(this); updateExpressionString();}
        void removeTerm(int i) override {terms.erase(terms.begin() + i); updateExpressionString();}
        
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
                            while (termsEqual){ // make sure loop doesnt continue past the end of terms
                                if (!terms[indexThis]->isEqual(otherContainer->getTerms()[indexOther])){
                                    termsEqual = false;
                                }
                                indexThis ++;
                                indexOther ++;
                            }
                            return termsEqual; // return true if all components are the same, false if else
                        }
                        
                        
                    }else if (operationType == OperationType::Division){
                        if (terms[1]->isLikeTerm(otherContainer->getTerms()[1])){ // if denom is the same, return true, they two numerators can be added
                            return true;
                        }else{
                            return false;
                        }
                    }else{ // you can always add one polynomial to another, just end up with a bigger polynomial, program this elsewhere
                        if (terms.size() != otherContainer->getTerms().size()){
                            return false;
                        }else{
                            bool termsEqual = true;
                            for (int i = 0; i < terms.size(); i ++){
                                if (!terms[i]->isLikeTerm(otherContainer->getTerms()[i])){
                                    termsEqual = false;
                                }
                            }
                            return termsEqual;
                        }
                    }
                }
            }else{
                return false;
            }
        }

        TermBase* factor() override {
            TermContainer* factoredContainer = new TermContainer();

            if (operationType == OperationType::Multiplication){
                factoredContainer->setOperationType(OperationType::Multiplication);
                for (int i = 0; i < terms.size(); i ++){
                    TermBase* factoredTerm = terms[i]->factor();
                    factoredContainer->appendTerm(factoredTerm);
                }
            }else if (operationType == OperationType::Division){
                factoredContainer->setOperationType(OperationType::Division);
                for (int i = 0; i < terms.size(); i ++){
                    TermBase* factoredTerm = terms[i]->factor();
                    factoredContainer->appendTerm(factoredTerm);
                }
            }else{
                factoredContainer->setOperationType(OperationType::Summation);

            }
            return this;
        }

        vector<TermBase*> allFactors() override {
            vector<TermBase*> dummy;
            return dummy;
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
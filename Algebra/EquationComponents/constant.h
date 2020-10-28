#pragma once

#include <string>
#include <vector>
#include "variable.h"
#include "termContainer.h"

using namespace std;

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

        TermBase* sum(TermBase* other) override {
            Constant* otherConstant = dynamic_cast<Constant*> (other);

            if (otherConstant){
                int newConstant = constant + otherConstant->getConstant();
                if (newConstant < 0){
                    return new Constant(false, nullptr, nullptr, newConstant);
                }else{
                    return new Constant(true, nullptr, nullptr, newConstant);
                }
            }else{
                TermContainer* newContainer = new TermContainer();
                newContainer->setOperationType(OperationType::Summation);
                newContainer->appendTerm(this);
                newContainer->appendTerm(other);
                return newContainer;
            }
        }

        TermBase* multiply(TermBase* other) override {
            Constant* otherConstant = dynamic_cast<Constant*> (other);

            if (otherConstant){
                int newConstant = constant * otherConstant->getConstant();
                if (newConstant < 0){
                    return new Constant(false, nullptr, nullptr, newConstant);
                }else{
                    return new Constant(true, nullptr, nullptr, newConstant);
                }
            }else{
                TermContainer* newContainer = new TermContainer();
                newContainer->setOperationType(OperationType::Multiplication);
                newContainer->appendTerm(this);
                newContainer->appendTerm(other);
                return newContainer;
            }
        }

        TermBase* divide(TermBase* other) override {
            Constant* otherConstant = dynamic_cast<Constant*> (other);

            if (otherConstant){
                int newConstant = constant / otherConstant->getConstant();
                if (newConstant < 0){
                    return new Constant(false, nullptr, nullptr, newConstant);
                }else{
                    return new Constant(true, nullptr, nullptr, newConstant);
                }
            }else{
                TermContainer* newContainer = new TermContainer();
                newContainer->setOperationType(OperationType::Division);
                newContainer->appendTerm(this);
                newContainer->appendTerm(other);
                return newContainer;
            }
        }

        TermBase* factor() override {
            return this;
        }

        vector<TermBase*> allFactors() override {
            vector<TermBase*> factors;
            for (int i = 0; i <= constant; i ++){
                if (constant % i == 0){
                    Constant* factor = new Constant(true, nullptr, nullptr, i);
                    factors.push_back(factor);
                }
            }
            return factors;
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
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
        string representation;
    public:
        TermBase(): sign(1), root(nullptr), exponent(nullptr), parentExpression(nullptr){}
        TermBase(bool sign, TermBase* root, TermBase* exponent): sign(sign), root(root), exponent(exponent), parentExpression(nullptr){}

        bool getSign(){return sign;}
        TermBase* getRoot(){return root;}
        TermBase* getExponent(){return exponent;}
        TermBase* getParentExpression(){return parentExpression;}
        string getRepresentation(){return representation;}

        void setSign(bool s){sign = s;}
        void setRoot(TermBase* r){root = r;}
        void setExponent(TermBase* e){exponent = e;}
        void setParentExpression(TermBase* p){parentExpression = p;}
        void updateRepresentation(){representation = this->toString();}
        bool isEqual(TermBase* other){if (representation == other->getRepresentation()){return true;}else{return false;}}

        // methods to override

        virtual void appendTerm(TermBase* t){}
        virtual void removeTerm(TermBase* t){}
        virtual void removeTerm(int index){}

        virtual TermBase* getCoefficient(){return nullptr;}
        virtual void setCoefficient(TermBase* c){}

        virtual bool isOne(){return false;}
        virtual bool isSummable(TermBase* other){return false;}
        virtual vector<TermBase*> allFactors(){vector<TermBase*> dummy; return dummy;}
        virtual TermBase* factorTerm(bool high){return nullptr;}

        virtual string toString(){return "term base";}
    
};

class Constant : public TermBase {
    private:
        int constant;
    public:
        Constant(): TermBase(){}
        Constant(bool sign, TermBase* root, TermBase* exponent, int constant): TermBase(sign, root, exponent), constant(constant){updateRepresentation();}

        int getConstant(){return constant;}
        void setConstant(int c){constant = c;}

        string toString() override {
            string termStr = "";
            if (!sign){
                termStr += '-';
            }

            termStr += to_string(constant);

            if (root != nullptr){
                if (!root->isOne()){
                    termStr = '(' + root->toString() + '|' + termStr + ')';
                }
            }
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    termStr = termStr + "^(" + exponent->toString() + ')';
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
        Variable(bool sign, TermBase* root, TermBase* exponent, char variable): TermBase(sign, root, exponent), variable(variable){updateRepresentation();}

        char getVariable(){return variable;}
        void setVariable(char v){variable = v;}

        string toString() override {
            string termStr = "";
            if (!sign){
                termStr += '-';
            }

            termStr += variable;

            if (root != nullptr){
                if (!root->isOne()){
                    termStr = '(' + root->toString() + '|' + termStr + ')';
                }
            }
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    termStr = termStr + "^(" + exponent->toString() + ')';
                }
            }

            return termStr;
        }

};

class TermContainer : public TermBase {
    private:
        vector<TermBase*> terms;
        OperationType operationType;
    public:
        TermContainer(): TermBase(){}
        TermContainer(bool sign, TermBase* root, TermBase* exponent): TermBase(sign, root, exponent){updateRepresentation();}

        vector<TermBase*> getTerms(){return terms;}
        OperationType getOperationType(){return operationType;}
        void setTerms(vector<TermBase*> t){terms = t;}
        void setOperationType(OperationType o){operationType = o;}

        void appendTerm(TermBase* t) override {terms.push_back(t); updateRepresentation();}
        void removeTerm(int i) override {terms.erase(terms.begin() + i); updateRepresentation();}
        TermBase* getCoefficient() override {return terms[0];}
        void setCoefficient(TermBase* c) override {terms[0] = c;}
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
                    termStr = '(' + termStr + ')';
                }
            }

            if (root != nullptr){
                if (!root->isOne()){
                    termStr = '(' + root->toString() + '|' + termStr + ')';
                }
            }
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    termStr = termStr + "^(" + exponent->toString() + ')';
                }
            }


            return termStr;
        }
};


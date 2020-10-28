#pragma once

#include <string>
#include <vector>

using namespace std;

enum class OperationType{
    Summation,
    Multiplication,
    Division
};

vector<int> allFactors(int target){
    vector<int> factors;
    for (int i = 0; i <= target; i ++){
        if (target % i == 0){
            factors.push_back(i);
        }
    }
    return factors;
}

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

        virtual TermBase* factor() = 0;
        virtual vector<TermBase*> allFactors() = 0;

        virtual TermBase* copy(){return nullptr;}
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
                Constant* otherConstant = dynamic_cast<Constant*> (other);
                Variable* otherVariable = dynamic_cast<Variable*> (other);
                if (otherConstant){
                    return false;
                }
                if (otherVariable){
                    return true;
                }
            }
        }

        TermBase* sum(TermBase* other){
            Variable* otherVariable = dynamic_cast<Variable*> (other);

            TermContainer* newContainer = new TermContainer();

            if (otherVariable){
                if (otherVariable->getVariable() == variable){
                    Constant* newCoefficient = new Constant(true, nullptr, nullptr, 2);
                    newContainer->setOperationType(OperationType::Multiplication);
                    newContainer->appendTerm(newCoefficient);
                    newContainer->appendTerm(otherVariable);
                    return newContainer;
                }else{
                    newContainer->setOperationType(OperationType::Summation);
                    newContainer->appendTerm(this);
                    newContainer->appendTerm(otherVariable);
                    return newContainer;
                }
            }else{
                newContainer->setOperationType(OperationType::Summation);
                newContainer->appendTerm(this);
                newContainer->appendTerm(other);
                return newContainer;
            }
        }

        TermBase* multiply(TermBase* other){
            Variable* otherVariable = dynamic_cast<Variable*> (other);

            TermContainer* newContainer = new TermContainer();

            if (otherVariable){
                if (otherVariable->getVariable() == variable){
                    Constant* exponent = new Constant(true, nullptr, nullptr, 2);
                    Variable* newVariable;
                    if (sign != otherVariable->getSign()){
                        newVariable = new Variable(false, nullptr, exponent, variable);
                    }else{
                        newVariable = new Variable(true, nullptr, exponent, variable);
                    }
                    return newVariable;
                }else{
                    newContainer->setOperationType(OperationType::Multiplication);
                    newContainer->appendTerm(this);
                    newContainer->appendTerm(otherVariable);
                    return newContainer;
                }
            }else{
                newContainer->setOperationType(OperationType::Multiplication);
                newContainer->appendTerm(this);
                newContainer->appendTerm(other);
                return newContainer;
            }
        }

        TermBase* divide(TermBase* other){
            Variable* otherVariable = dynamic_cast<Variable*> (other);

            TermContainer* newContainer = new TermContainer();

            if (otherVariable){
                if (otherVariable->getVariable() == variable){
                    Constant* one;
                    if (sign != otherVariable->getSign()){
                        one = new Constant(false, nullptr, nullptr, 1);
                    }else{
                        one = new Constant(true, nullptr, nullptr, 1);
                    }
                    return one;
                }else{
                    newContainer->setOperationType(OperationType::Division);
                    newContainer->appendTerm(this);
                    newContainer->appendTerm(otherVariable);
                    return newContainer;
                }
            }else{
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
            if ()
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


#pragma once

#include <string>
#include <vector>

using namespace std;

int factor(int value, bool high){
    if (high){
        for (int i = value; i > 0; i --){
            if (value % i == 0){
                return i;
            }
        }
    }else{
        for (int i = 1; i < value; i ++){
            if (value % i == 0){
                return i;
            }
        }
    }
}

vector<int> allIntFactors(int value){
    vector<int> factors;
    for (int i = 0; i < value; i ++){
        if (value % i == 0){
            factors.push_back(i);
        }
    }
    return factors;
}

enum class ExpressionType{
    Empty,
    Monomial,
    Binomial,
    Trinomial,
    Polynomial
};

class TermBase {
    protected:
        bool sign;
        //int coefficient;
        TermBase* exponent;
        TermBase* parentExpression;
        string representation;
    public:
        TermBase(): sign(1), exponent(nullptr), parentExpression(nullptr){}
        TermBase(bool sign, TermBase* exponent): sign(sign), exponent(exponent), parentExpression(nullptr){}
        //TermBase(): sign(1), coefficient(1), exponent(nullptr), parentExpression(nullptr){}
        //TermBase(bool sign, int coefficient, TermBase* exponent): sign(sign), coefficient(coefficient), exponent(exponent), parentExpression(nullptr){}
        bool getSign(){return sign;}
        //int getCoefficient(){return coefficient;}
        TermBase* getExponent(){return exponent;}
        TermBase* getParentExpression(){return parentExpression;}
        string getRepresentation(){return representation;}
        void setSign(bool s){sign = s;}
        //void setCoefficient(int c){coefficient = c;}
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

template<typename t>

class AtomicTerm : public TermBase {
    private:
        t value;
    public:
        AtomicTerm(): TermBase(){}
        AtomicTerm(bool sign, TermBase* exponent, t value): TermBase(sign, exponent), value(value){updateRepresentation();}
        t getValue(){return value;}
        void setValue(t v){value = v; updateRepresentation();}

        // overridden methods

        void appendTerm(TermBase* tb) override {}
        void removeTerm(TermBase* t) override {}
        void removeTerm(int index) override {}
        bool isOne() override {return false;}
        bool isSimpleNumeric() override {return false;}
        bool isSummable(TermBase* other) override {return false;}
        vector<TermBase*> allFactors() override {vector<TermBase*> dummy; return dummy;}
        TermBase* factorTerm(bool high) override {return nullptr;}
        TermBase* compute() override {return nullptr;}
        string toString() override {return "unknown atomic type";}

};

template<>

class AtomicTerm<char> : public TermBase {
    private:
        char value;
    public:
        AtomicTerm(): TermBase(){}
        AtomicTerm(bool sign, TermBase* exponent, char value): TermBase(sign, exponent), value(value){updateRepresentation();}
        char getValue(){return value;}
        void setValue(char v){value = v; updateRepresentation();}

        // overriden methods

        void appendTerm(TermBase* tb) override {}
        void removeTerm(TermBase* t) override {}
        void removeTerm(int index) override {}
        bool isOne() override {return false;}
        bool isSimpleNumeric() override {return false;}
        bool isSummable(TermBase* other) override {return false;}
        vector<TermBase*> allFactors() override {
            vector<TermBase*> factors;
            if (exponent == nullptr){
                factors.push_back(this);
            }else{
                if (exponent->isOne()){
                    factors.push_back(this);
                }else{
                    //int power = exponent
                }
            }
            

        }
        TermBase* factorTerm(bool high) override {return this;}
        TermBase* compute() override {return this;}
        string toString() override {
            string termStr = "";
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    string totalTerm = value + "^(" + exponent->toString() + ')';
                }
            }else{
                return termStr + value;
            }
        }

};

template<>

class AtomicTerm<int> : public TermBase {
    private:
        int value;
    public:
        AtomicTerm(): TermBase(){}
        AtomicTerm(bool sign, TermBase* exponent, int value): TermBase(sign, exponent), value(value){updateRepresentation();}
        int getValue(){return value;}
        void setValue(int v){value = v; updateRepresentation();}
        
        // overriden methods

        void appendTerm(TermBase* tb) override {}
        void removeTerm(TermBase* t) override {}
        void removeTerm(int index) override {}
        bool isOne() override {if (value == 1){return true;}else{return false;}}
        bool isSimpleNumeric() override {return true;}
        bool isSummable(TermBase* other) override {return false;}
        TermBase* factorTerm(bool high) override {
            int factorVal = factor(value, high);
            return new AtomicTerm<int>(true, nullptr, factorVal);
        }
        TermBase* compute() override {return this;}
        string toString() override {
            if (exponent != nullptr){
                if (!exponent->isOne()){
                    string totalTerm = to_string(value) + "^(" + exponent->toString() + ')';
                }else{
                    return to_string(value);
                }
            }else{
                return to_string(value);
            }
        }
};

class CompoundTerm : public TermBase {
    private:
        vector<TermBase*> terms;
        AtomicTerm<int>* coefficient;
    public:
        CompoundTerm(): TermBase(), coefficient(nullptr){}
        CompoundTerm(bool sign, TermBase* exponent, vector<TermBase*> terms, AtomicTerm<int>* coefficient): TermBase(sign, exponent), terms(terms), coefficient(coefficient){}
        vector<TermBase*> getTerms(){return terms;}
        AtomicTerm<int>* getCoefficient(){return coefficient;}
        void setTerms(vector<TermBase*> tb){terms = tb; updateRepresentation();}
        void setCoefficient(AtomicTerm<int>* c){coefficient = c;}
        

        // overriden methods

        void appendTerm(TermBase* tb) override {
            if (tb != nullptr){
                terms.push_back(tb);
                tb->setParentExpression(this);
                updateRepresentation();
            } 
        }
        void removeTerm(TermBase* t) override {}
        void removeTerm(int index) override {}
        
        bool isOne() override {return false;}
        bool isSimpleNumeric() override {return false;}
        bool isSummable(CompoundTerm* other){
            bool equal = true;
            if (terms.size() != other->getTerms().size()){
                return false;
            }else{
                for (int i = 0; i < terms.size(); i ++){
                    if (!terms[i]->isEqual(other->getTerms()[i])){
                        equal = false;
                    }
                }
            }
            return equal;
        }
        TermBase* factor(bool high){
            // do polynomial first
        }
        TermBase* compute() override {return nullptr; /*return product*/}
        string toString() override {
            if (terms.size() != 0){
                string termStr = "";
                
                if (parentExpression == nullptr){
                    if (!sign){
                        termStr += '-';
                    }
                }
                if (coefficient->getValue() != 1){
                    termStr += coefficient->toString();
                }
                for (int i = 0; i < terms.size(); i ++){
                    termStr += terms[i]->toString();   
                }
                if (exponent != nullptr){
                    if (!exponent->isOne()){
                        termStr += "^(" + exponent->toString() + ')';
                    }
                }
                
                return termStr;
            }
            return "empty compound";
        }

};

class Expression : public TermBase {
    private:
        vector<TermBase*> terms;
        ExpressionType type;
        TermBase* degree;
    public:
        Expression(): TermBase(), type(ExpressionType::Empty){}
        Expression(bool sign, TermBase* exponent, vector<TermBase*> terms): TermBase(sign, exponent), terms(terms){
            updateType();
            updateRepresentation();
            }
        vector<TermBase*> getTerms(){return terms;}
        void setTerms(vector<TermBase*> tb){
            terms = tb;
            updateType();
            updateRepresentation();
        }
        void appendTerm(TermBase* tb) override {
            if (tb != nullptr){
                terms.push_back(tb);
                tb->setParentExpression(this);
                updateType();
                updateRepresentation();
            }
        }
        void updateType(){
            if (terms.size() == 0){
                type = ExpressionType::Empty;
            }else if (terms.size() == 1){
                type = ExpressionType::Monomial;
            }else if (terms.size() == 2){
                type = ExpressionType::Binomial;
            }else if (terms.size() == 3){
                type = ExpressionType::Trinomial;
            }else{
                type = ExpressionType::Polynomial;
            }
        }
        bool isOne() override {return false;}
        bool isSimpleNumeric() override {return false;}
        bool isSummable(CompoundTerm* other) override {return false;}
        TermBase* sumLikeTerms(){
            for(int i = 0; i < terms.size(); i ++){
                TermBase* currentTerm = terms[i];
                for (int j = i + 1; j < terms.size(); j ++){
                    TermBase* comparedTerm = terms[j];
                    if (currentTerm->isSummable(comparedTerm)){
                        //int newCoefficient = currentTerm->
                    }
                }
            }
        }
        TermBase* factorTerm(bool high){
            
        }
        TermBase* compute() override {return nullptr; /*return sum*/}
        string toString() override {
            if (terms.size() != 0){
                string termStr = "";
                
                int n = terms.size();
                for (int i = 0; i < terms.size(); i ++){
                    if (i != 0){
                        if (terms[i]->getSign()){
                            termStr += '+';
                        }else{
                            termStr += '-';
                        }
                    }
                    termStr += terms[i]->toString();
                }

                if (terms.size() > 1){
                    termStr = "(" + termStr + ")";
                }

                if (exponent != nullptr){
                    if (!exponent->isOne()){
                        termStr += "^(" + exponent->toString() + ')';
                    }
                }
                
                
                return termStr;
            }
            return "empty expression";
        }
};

class RationalExpression : public TermBase {
    private:
        TermBase* num;
        TermBase* denom;
    public:
        RationalExpression(): TermBase(){num = nullptr; denom = nullptr;}
        RationalExpression(bool sign, TermBase* exponent, TermBase* num, TermBase* denom): TermBase(sign, exponent), num(num), denom(denom){updateRepresentation();}
        TermBase* getNum(){return num;}
        TermBase* getDenom(){return denom;}
        void setNum(TermBase* n){num = n; updateRepresentation();}
        void setDenom(TermBase* d){denom = d; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
        bool isOne() override {return false;}
        bool isSimpleNumeric() override {return false;}
        bool isSummable(TermBase* other) override {return false;}
        TermBase* compute() override {return nullptr; /*return quotient*/}
        string toString() override {
            if (num != nullptr & denom != nullptr){
                string termStr;
                if (num->getSign() & denom->getSign()){
                    termStr = "{" + num->toString() + '/' + denom->toString() + '}';
                }else if (num->getSign() & !denom->getSign()){
                    termStr = "{" + num->toString() + "/-" + denom->toString() + '}';
                }else if (!num->getSign() & denom->getSign()){
                    termStr = "{-" + num->toString() + '/' + denom->toString() + '}';
                }else{
                    termStr = "{-" + num->toString() + "/-" + denom->toString() + '}';
                }
                if (exponent != nullptr){
                    if (!exponent->isOne()){
                        string totalTerm = termStr + "^(" + exponent->toString() + ')';
                        return totalTerm;
                    }
                }else{
                    return termStr;
                }
            }
            return "incomplete rational";
        }
};

class RadicalExpression : public TermBase {
    private:
        TermBase* root;
        TermBase* term;
    public:
        RadicalExpression(): TermBase(), root(nullptr), term(nullptr){}
        RadicalExpression(bool sign, TermBase* root, TermBase* term): TermBase(sign, nullptr), root(root), term(term){updateRepresentation();}
        TermBase* getRoot(){return root;}
        TermBase* getTerm(){return term;}
        void setRoot(TermBase* r){root = r; updateRepresentation();}
        void setTerm(TermBase* tb){term = tb; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
        bool isOne() override {return false;}
        bool isSimpleNumeric() override {return false;}
        bool isSummable(CompoundTerm* other) override {return false;}
        TermBase* compute() override {return nullptr; /*return root*/}
        string toString() override {
            if (root != nullptr & term != nullptr){
                return "[" + root->toString() + "](" + term->toString() + ')';
            }else{
                return "incomplete radical";
            }
            
        }
};

class LogarithmicExpression : public TermBase {
    private:

    public:
        LogarithmicExpression(): TermBase(){}
};


#pragma once

#include <string>
#include <vector>

using namespace std;

class TermBase {
    protected:
        bool sign;
        int exponent;
    public:
        TermBase(){}
        TermBase(bool sign, int exponent): sign(sign), exponent(exponent){}
        bool getSign(){return sign;}
        int getExponent(){return exponent;}
        void setSign(bool s){sign = s;}
        void setExponent(int e){exponent = e;}
        virtual void appendTerm(TermBase* t){}
        virtual TermBase* compute(){return nullptr;} // either compute lowest term or real number
        virtual string toString(){return "term base";}
    
};

template<typename t>

class AtomicTerm : public TermBase {
    private:
        t value;
    public:
        AtomicTerm(){}
        AtomicTerm(bool sign, int exponent, t value): TermBase(sign, exponent), value(value){}
        t getValue(){return value;}
        void setValue(t v){value = v;}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return this;}
        string toString() override {
            return "unknown type";
        }

};

template<>

class AtomicTerm<char> : public TermBase {
    private:
        char value;
    public:
        AtomicTerm(){}
        AtomicTerm(bool sign, int exponent, char value): TermBase(sign, exponent), value(value){}
        char getValue(){return value;}
        void setValue(char v){value = v;}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return this;}
        string toString() override {
            string termStr;
            /*
            if (!sign){
                termStr = '-';
            }else{
                termStr = '+';
            }
            */
            termStr += value;
            return termStr;
        }

};

template<>

class AtomicTerm<int> : public TermBase {
    private:
        int value;
    public:
        AtomicTerm(){}
        AtomicTerm(bool sign, int exponent, int value): TermBase(sign, exponent), value(value){}
        int getValue(){return value;}
        void setValue(int v){value = v;}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return this;}
        string toString() override {
            char c = '0' + value;
            string termStr;
            /*
            if (!sign){
                termStr = '-';
            }else{
                termStr = '+';
            }
            */
            termStr += c;
            return termStr;
        }

};

class CompoundTerm : public TermBase {
    private:
        vector<TermBase*> terms;
    public:
        CompoundTerm(){}
        CompoundTerm(bool sign, int exponent, vector<TermBase*> terms): TermBase(sign, exponent), terms(terms){}
        vector<TermBase*> getTerms(){return terms;}
        void setTerms(vector<TermBase*> tb){terms = tb;}
        void appendTerm(TermBase* tb) override {terms.push_back(tb);}
        TermBase* compute() override {return nullptr; /*return product*/}
        string toString() override {
            string termStr = "";
            if (!sign){
                termStr += '-';
            }else{
                termStr += '+';
            }
            for (int i = 0; i < terms.size(); i ++){
                termStr += terms[i]->toString();   
            }
            return termStr;
        }

};

class Polynomial : public TermBase {
    private:
        vector<TermBase*> terms;
    public:
        Polynomial(){}
        Polynomial(bool sign, int exponent, vector<TermBase*> terms): TermBase(sign, exponent), terms(terms){}
        vector<TermBase*> getTerms(){return terms;}
        void setTerms(vector<TermBase*> tb){terms = tb;}
        void appendTerm(TermBase* tb) override {terms.push_back(tb);}
        TermBase* compute() override {return nullptr; /*return sum*/}
        string toString() override {
            string termStr = "";
            if (!sign){
                termStr += "-(";
            }else{
                termStr += "+(";
            }
            int n = terms.size();
            for (int i = 0; i < terms.size(); i ++){
                termStr += terms[i]->toString();
            }
            termStr += ')';
            return termStr;
        }
};

class RationalExpression : public TermBase {
    private:
        TermBase* num;
        TermBase* denom;
    public:
        RationalExpression(){}
        RationalExpression(bool sign, int exponent, TermBase* num, TermBase* denom): TermBase(sign, exponent), num(num), denom(denom){}
        TermBase* getNum(){return num;}
        TermBase* getDenom(){return denom;}
        void setNum(TermBase* n){num = n;}
        void setDenom(TermBase* d){denom = d;}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return nullptr; /*return quotient*/}
        string toString() override {
            string termStr;
            if (!sign){
                termStr = "-{" + num->toString() + '/' + denom->toString() + '}';
            }else{
                termStr = "+{" + num->toString() + '/' + denom->toString() + '}';
            }
            return termStr;
        }
};

class RadicalExpression : public TermBase {
    private:
        int root;
        TermBase* term;
    public:
        RadicalExpression(){}
        RadicalExpression(bool sign, int root, TermBase* term): TermBase(sign, 0), root(root), term(term){}
        int getRoot(){return root;}
        TermBase* getTerm(){return term;}
        void setRoot(int r){root = r;}
        void setTerm(TermBase* tb){term = tb;}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return nullptr; /*return root*/}
        string toString() override {return "";}
};


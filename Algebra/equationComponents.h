#pragma once

#include <string>
#include <vector>

using namespace std;

class Term {
    protected:
        bool sign;
        int exponent;
    public:
        Term(){}
        Term(bool sign, int exponent): exponent(exponent){}
        bool getSign(){return sign;}
        int getExponent(){return exponent;}
        void setSign(bool s){sign = s;}
        void setExponent(int e){exponent = e;}
        virtual Term* compute(){return nullptr;} // either compute lowest term or real number
    
};

template<typename t>

class AtomicTerm : public Term {
    private:
        t value;
    public:
        AtomicTerm(){}
        AtomicTerm(bool sign, int exponent, t value): Term(sign, exponent), value(value){}
        t getValue(){return t;}
        void setValue(t v){value = v;}

};

class ComplexTerm : public Term {
    private:
        vector<Term> terms;
    public:
        ComplexTerm(){}
        ComplexTerm(bool sign, int exponent, vector<Term> terms): Term(sign, exponent), terms(terms){}
        vector<Term> getTerms(){return terms;}
        void setTerms(vector<Term> t){terms = t;}
        void appendTerm(Term t){terms.push_back(t);}
};

class Expression : public Term {
    private:
        vector<Term> terms;
        string nomialType;
    public:
        Expression(){}
        Expression(bool sign, int exponent, vector<Term> terms): Term(sign, exponent), terms(terms){}
        vector<Term> getTerms(){return terms;}
        string getNomialType(){return nomialType;}
        void setTerms(vector<Term> t){terms = t;}
        void appendTerm(Term t){terms.push_back(t);}
        void setNomialType(string n){nomialType = n;}
};

class RationalExpression : public Term {
    private:
        Term* num;
        Term* denom;
    public:
        RationalExpression(){}
        RationalExpression(bool sign, int exponent, Term* num, Term* denom): Term(sign, exponent), num(num), denom(denom){}
        Term* getNum(){return num;}
        Term* getDenom(){return denom;}
        void setNum(Term* n){num = n;}
        void setDenom(Term* d){denom = d;}
};

class RadicalExpression : public Term {
    private:
        int root;
        Term* term;
    public:
        RadicalExpression(){}
        RadicalExpression(bool sign, int root, Term* term): Term(sign, 0), root(root), term(term){}
        int getRoot(){return root;}
        Term* getTerm(){return term;}
        void setRoot(int r){root = r;}
        void setTerm(Term* t){term = t;}
};


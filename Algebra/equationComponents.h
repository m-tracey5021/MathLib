#pragma once

#include <string>
#include <vector>

using namespace std;

class TermBase {
    protected:
        bool sign;
        int exponent;
        string representation;
        TermBase* parentExpression;
    public:
        TermBase(): sign(1), exponent(1), parentExpression(nullptr){}
        TermBase(bool sign, int exponent): sign(sign), exponent(exponent), parentExpression(nullptr){}
        bool getSign(){return sign;}
        int getExponent(){return exponent;}
        string getRepresentation(){return representation;}
        TermBase* getParentExpression(){return parentExpression;}
        void setSign(bool s){sign = s;}
        void setExponent(int e){exponent = e;}
        void updateRepresentation(){representation = this->toString();}
        void setParentExpression(TermBase* p){parentExpression = p;}
        virtual void appendTerm(TermBase* t){}
        virtual TermBase* compute(){return nullptr;} // either compute lowest term or real number
        virtual string toString(){return "term base";}
    
};

template<typename t>

class AtomicTerm : public TermBase {
    private:
        t value;
    public:
        AtomicTerm(): TermBase(){}
        AtomicTerm(bool sign, int exponent, t value): TermBase(sign, exponent), value(value){updateRepresentation();}
        t getValue(){return value;}
        void setValue(t v){value = v; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return this;}
        string toString() override {
            return "unknown atomic type";
        }

};

template<>

class AtomicTerm<char> : public TermBase {
    private:
        char value;
    public:
        AtomicTerm(): TermBase(){}
        AtomicTerm(bool sign, int exponent, char value): TermBase(sign, exponent), value(value){updateRepresentation();}
        char getValue(){return value;}
        void setValue(char v){value = v; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return this;}
        string toString() override {string termStr; termStr += value; return termStr;}

};

template<>

class AtomicTerm<int> : public TermBase {
    private:
        int value;
    public:
        AtomicTerm(): TermBase(){}
        AtomicTerm(bool sign, int exponent, int value): TermBase(sign, exponent), value(value){updateRepresentation();}
        int getValue(){return value;}
        void setValue(int v){value = v; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return this;}
        string toString() override {return to_string(value);}

};

class CompoundTerm : public TermBase {
    private:
        vector<TermBase*> terms;
    public:
        CompoundTerm(): TermBase(){}
        CompoundTerm(bool sign, int exponent, vector<TermBase*> terms): TermBase(sign, exponent), terms(terms){}
        vector<TermBase*> getTerms(){return terms;}
        void setTerms(vector<TermBase*> tb){terms = tb; updateRepresentation();}
        void appendTerm(TermBase* tb) override {
            if (tb != nullptr){
                terms.push_back(tb);
                tb->setParentExpression(this);
                updateRepresentation();
            } 
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
                for (int i = 0; i < terms.size(); i ++){
                    termStr += terms[i]->toString();   
                }
                return termStr;
            }
            return "empty compound";
        }

};

class Polynomial : public TermBase {
    private:
        vector<TermBase*> terms;
    public:
        Polynomial(): TermBase(){}
        Polynomial(bool sign, int exponent, vector<TermBase*> terms): TermBase(sign, exponent), terms(terms){updateRepresentation();}
        vector<TermBase*> getTerms(){return terms;}
        void setTerms(vector<TermBase*> tb){terms = tb; updateRepresentation();}
        void appendTerm(TermBase* tb) override {
            if (tb != nullptr){
                terms.push_back(tb);
                tb->setParentExpression(this);
                updateRepresentation();
            }
        }
        TermBase* compute() override {return nullptr; /*return sum*/}
        string toString() override {
            if (terms.size() != 0){
                string termStr = "(";
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
                termStr += ')';
                return termStr;
            }
            return "empty polynomial";
        }
};

class RationalExpression : public TermBase {
    private:
        TermBase* num;
        TermBase* denom;
    public:
        RationalExpression(): TermBase(){num = nullptr; denom = nullptr;}
        RationalExpression(bool sign, int exponent, TermBase* num, TermBase* denom): TermBase(sign, exponent), num(num), denom(denom){updateRepresentation();}
        TermBase* getNum(){return num;}
        TermBase* getDenom(){return denom;}
        void setNum(TermBase* n){num = n; updateRepresentation();}
        void setDenom(TermBase* d){denom = d; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
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
                return termStr;
            }
            return "incomplete rational";
        }
};

class RadicalExpression : public TermBase {
    private:
        int root;
        TermBase* term;
    public:
        RadicalExpression(): TermBase(){}
        RadicalExpression(bool sign, int root, TermBase* term): TermBase(sign, 0), root(root), term(term){updateRepresentation();}
        int getRoot(){return root;}
        TermBase* getTerm(){return term;}
        void setRoot(int r){root = r; updateRepresentation();}
        void setTerm(TermBase* tb){term = tb; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
        TermBase* compute() override {return nullptr; /*return root*/}
        string toString() override {return "";}
};


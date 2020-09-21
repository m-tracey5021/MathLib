#pragma once

#include <string>
#include <vector>

using namespace std;

class TermBase {
    protected:
        bool sign;
        string representation;
        TermBase* exponent;
        TermBase* parentExpression;
    public:
        TermBase(): sign(1), exponent(nullptr), parentExpression(nullptr){}
        TermBase(bool sign, TermBase* exponent): sign(sign), exponent(exponent), parentExpression(nullptr){}
        bool getSign(){return sign;}
        string getRepresentation(){return representation;}
        TermBase* getExponent(){return exponent;}
        TermBase* getParentExpression(){return parentExpression;}
        void setSign(bool s){sign = s;}
        void updateRepresentation(){representation = this->toString();}
        void setExponent(TermBase* e){exponent = e;}
        void setParentExpression(TermBase* p){parentExpression = p;}
        virtual void appendTerm(TermBase* t){}
        virtual bool isOne(){return false;}
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
        void appendTerm(TermBase* tb) override {}
        bool isOne(){return false;}
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
        AtomicTerm(bool sign, TermBase* exponent, char value): TermBase(sign, exponent), value(value){updateRepresentation();}
        char getValue(){return value;}
        void setValue(char v){value = v; updateRepresentation();}
        void appendTerm(TermBase* tb) override {}
        bool isOne(){return false;}
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
        void appendTerm(TermBase* tb) override {}
        bool isOne(){if (value == 1){return true;}else{return false;}}
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
    public:
        CompoundTerm(): TermBase(){}
        CompoundTerm(bool sign, TermBase* exponent, vector<TermBase*> terms): TermBase(sign, exponent), terms(terms){}
        vector<TermBase*> getTerms(){return terms;}
        void setTerms(vector<TermBase*> tb){terms = tb; updateRepresentation();}
        void appendTerm(TermBase* tb) override {
            if (tb != nullptr){
                terms.push_back(tb);
                tb->setParentExpression(this);
                updateRepresentation();
            } 
        }
        bool isOne(){return false;}
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

class Polynomial : public TermBase {
    private:
        vector<TermBase*> terms;
    public:
        Polynomial(): TermBase(){}
        Polynomial(bool sign, TermBase* exponent, vector<TermBase*> terms): TermBase(sign, exponent), terms(terms){updateRepresentation();}
        vector<TermBase*> getTerms(){return terms;}
        void setTerms(vector<TermBase*> tb){terms = tb; updateRepresentation();}
        void appendTerm(TermBase* tb) override {
            if (tb != nullptr){
                terms.push_back(tb);
                tb->setParentExpression(this);
                updateRepresentation();
            }
        }
        bool isOne(){return false;}
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
            return "empty polynomial";
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
        bool isOne(){return false;}
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
        bool isOne(){return false;}
        TermBase* compute() override {return nullptr; /*return root*/}
        string toString() override {
            if (root != nullptr & term != nullptr){
                return "[" + root->toString() + "](" + term->toString() + ')';
            }else{
                return "incomplete radical";
            }
            
        }
};


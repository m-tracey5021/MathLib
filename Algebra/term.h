#pragma once

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
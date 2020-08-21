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
        virtual Term* compute(){return nullptr;} // either compute lowest term or real number
    
};
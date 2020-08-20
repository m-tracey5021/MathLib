#pragma once

class Term {
    protected:
        int exponent;
    public:
        Term(){}
        Term(int exponent): exponent(exponent){}
        int getExponent(){return exponent;}
        virtual Term* compute(){return nullptr;} // either compute lowest term or real number
    
};
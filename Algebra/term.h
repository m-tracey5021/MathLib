#pragma once

class Term {
    protected:
        int exponent;
    public:
        Term(){}
        Term(int exponent): exponent(exponent){}
        virtual Term compute(){}
    
};
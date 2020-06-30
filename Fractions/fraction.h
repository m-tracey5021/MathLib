#pragma once

#include <iostream>

class Fraction {

    private:
        int num;
        int denum;
    public:
        Fraction();
        Fraction(int num, int denum);
        int getNum();
        int getDenum();
        Fraction add(Fraction other);
        Fraction subtract(Fraction other);
        Fraction multiply(Fraction other);
        Fraction divide(Fraction other);

        Fraction add(int num);
        Fraction subtract(int num);
        Fraction multiply(int num);
        Fraction divide(int num);

        void simplify();
        void reciprocate();

        std::string toString();
        

};
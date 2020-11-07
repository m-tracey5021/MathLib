#include "../Fractions/fraction.h"
#include <string>

bool testAdd(){
    Fraction fraction1(1, 3);
    Fraction fraction2(1, 3);
    Fraction fraction3(5, 8);
    Fraction fraction4(6, 9);
    Fraction fraction5(4, 5);

    Fraction added1 = fraction1.add(fraction2);
    Fraction added2 = fraction3.add(fraction4);
    Fraction added3 = fraction5.add(2);

    std::string addedStr1 = added1.toString();
    std::string addedStr2 = added2.toString();
    std::string addedStr3 = added3.toString();

    std::string expected1 = "6/9";
    std::string expected2 = "93/72";
    std::string expected3 = "14/5";

    if (addedStr1 == expected1 & 
    addedStr2 == expected2 & 
    addedStr3 == expected3){
        return true;
    }else{
        return false;
    }
}

bool testSimplify(){
    Fraction fraction1(8, 24);
    Fraction fraction2(3, 10);
    Fraction fraction3(52, 87);
    Fraction fraction4(160, 384);

    fraction1.simplify();
    fraction2.simplify();
    fraction3.simplify();
    fraction4.simplify();

    std::string fractionStr1 = fraction1.toString();
    std::string fractionStr2 = fraction2.toString();
    std::string fractionStr3 = fraction3.toString();
    std::string fractionStr4 = fraction4.toString();

    std::string expected1 = "1/3";
    std::string expected2 = "3/10";
    std::string expected3 = "52/87";
    std::string expected4 = "5/12";

    if (fractionStr1 == expected1 & 
    fractionStr2 == expected2 & 
    fractionStr3 == expected3 &
    fractionStr4 == expected4){
        return true;
    }else{
        return false;
    }
}
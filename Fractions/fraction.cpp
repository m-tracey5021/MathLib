#include "fraction.h"
#include "../basicArithmeticFunctions.h"
#include <vector>
#include <string>

Fraction::Fraction(){}

Fraction::Fraction(int numerator, int denumerator){
    num = numerator;
    denum = denumerator;
}

int Fraction::getNum(){
    return num;
}

int Fraction::getDenum(){
    return denum;
}

Fraction Fraction::add(Fraction other){
    int simpleCommonDenum = denum * other.getDenum();
    int multipliedFirstNum = num * other.getDenum();
    int multipliedSecondNum = denum * other.getNum();
    int resultantNum = multipliedFirstNum + multipliedSecondNum;
    Fraction added(resultantNum, simpleCommonDenum);
    return added;
}

Fraction Fraction::subtract(Fraction other){
    int simpleCommonDenum = denum * other.getDenum();
    int multipliedFirstNum = num * other.getDenum();
    int multipliedSecondNum = denum * other.getNum();
    int resultantNum;
    if (multipliedFirstNum > multipliedSecondNum){
        resultantNum = multipliedFirstNum - multipliedSecondNum;
    }else if (multipliedFirstNum < multipliedSecondNum){
        resultantNum = multipliedSecondNum - multipliedFirstNum;
    }else{
        resultantNum = 0;
    }
    Fraction subtracted(resultantNum, simpleCommonDenum);
    return subtracted;
}

Fraction Fraction::multiply(Fraction other){
    int newNum = num * other.getNum();
    int newDenum = denum * other.getDenum();
    Fraction multiplied(newNum, newDenum);
    return multiplied;
}

Fraction Fraction::divide(Fraction other){
    int newNum  = num * other.getDenum();
    int newDenum = denum * other.getNum();
    Fraction divided(newNum, newDenum);
    return divided;
}

Fraction Fraction::add(int num){
    Fraction wholeAsFraction(num, 1);
    return this->add(wholeAsFraction);
}

Fraction Fraction::subtract(int num){
    Fraction wholeAsFraction(num, 1);
    return this->subtract(wholeAsFraction);
}

Fraction Fraction::multiply(int num){
    Fraction wholeAsFraction(num, 1);
    return this->multiply(wholeAsFraction);
}

Fraction Fraction::divide(int num){
    Fraction wholeAsFraction(num, 1);
    return this->divide(wholeAsFraction);
}

void Fraction::simplify(){
    int lcm = largestCommonMultiple(num, denum);
    num = num / lcm;
    denum = denum / lcm;
}

void Fraction::reciprocate(){
    int tmpNum = num;
    num = denum;
    denum = tmpNum;
}

std::string Fraction::toString(){
    return std::to_string(num) + "/" + std::to_string(denum);
}
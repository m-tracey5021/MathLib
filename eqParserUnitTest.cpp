#include "UnitTests/eqParserUnitTest.h"
#include "Algebra/equationComponents.h"
#include "Algebra/eqParser.h"
#include <string>
#include <utility>
#include <iostream>

using namespace std;

bool testTermParse(){
    string expected1 = "2a";
    TermBase* term1 = parseTerm(expected1, 0, 1).first;
    string str1 = term1->toString();

    string expected2 = "3x+2/xy";
    TermBase* term2 = parsePolynomial(expected2);
    string str2 = term2->toString();

    if (expected1 == str1 & expected2 == str2){
        return true;
    }else{
        return false;
    }
}

bool testPolynomialParse(){
    return false;
}

bool testEquationParse(){
    return false;
}
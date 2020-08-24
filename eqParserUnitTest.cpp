#include "UnitTests/eqParserUnitTest.h"
#include "Algebra/equationComponents.h"
#include "Algebra/eqParser.h"
#include <string>
#include <utility>
#include <iostream>

using namespace std;

bool testTermParse(){
    string termStr = "2a";
    pair<TermBase*, int> terminatingInfo = parseTerm(termStr, 0, 1);
    TermBase* term1 = terminatingInfo.first;
    TermBase term2 = *terminatingInfo.first;

    string str1 = term1->toString();
    string str2 = term2.toString();
    cout << str1;
    cout << str2;
    return false;
}

bool testPolynomialParse(){
    return false;
}

bool testEquationParse(){
    return false;
}
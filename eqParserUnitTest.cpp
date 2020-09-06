#include "UnitTests/eqParserUnitTest.h"
#include "Algebra/equationComponents.h"
#include "Algebra/eqParser.h"
#include <string>
#include <utility>
#include <iostream>

using namespace std;

bool testExpressionParse(){
    
    string expression1 = "2a";
    string expected1 = "+2a";
    TermBase* term1 = parseTerm(expression1, 0, 1).first;
    string str1 = term1->toString();
    
    string expression2 = "3x+{2/xy}";
    string expected2 = "(3x+{2/xy})";
    TermBase* term2 = parseExpression(expression2, 0, 1).first;
    string str2 = term2->toString();

    string expression3 = "3x+{2/(xy+5t)}";
    string expected3 = "(3x+{2/(xy+5t)})";
    TermBase* term3 = parseExpression(expression3, 0, 1).first;
    string str3 = term3->toString();

    string expression4 = "(3x+5)(2a-6)";
    string expected4 = "((3x+5)(2a-6))";
    TermBase* term4 = parseExpression(expression4, 0, 1).first;
    string str4 = term4->toString();

    string expression5 = "31x+206y";
    string expected5 = "(31x+206y)";
    TermBase* term5 = parseExpression(expression5, 0, 1).first;
    string str5 = term5->toString();
    
    string expression6 = "(28x-42y)+(3x+7y)";
    string expected6 = "((28x-42y)+(3x+7y))";
    TermBase* term6 = parseExpression(expression6, 0, 1).first;
    string str6 = term6->toString();

    if (expected1 == str1 & expected2 == str2 & expected3 == str3){
        return true;
    }else{
        return false;
    }
}

bool testEquationParse(){
    return false;
}
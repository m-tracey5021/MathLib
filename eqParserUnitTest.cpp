#include "UnitTests/eqParserUnitTest.h"
#include "Algebra/equationComponents.h"
#include "Algebra/eqParser.h"
#include <string>
#include <utility>
#include <iostream>

using namespace std;

bool testExpressionParse(){
    
    string expression1 = "2a";
    string expected1 = "2a";
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

    string expression7 = "{(28x-42y)/(3x+7y)}";
    string expected7 = "{(28x-42y)/(3x+7y)}";
    TermBase* term7 = parseExpression(expression7, 0, 1).first;
    string str7 = term7->toString();

    string expression8 = "x^(2)";
    string expected8 = "x^(2)";
    TermBase* term8 = parseExpression(expression8, 0, 1).first;
    string str8 = term8->toString();

    string expression9 = "(28x-42y)^(23y+8)";
    string expected9 = "(28x-42y)^(23y+8)";
    TermBase* term9 = parseExpression(expression9, 0, 1).first;
    string str9 = term9->toString();

    string expression10 = "[2](x)";
    string expected10 = "[2](x)";
    TermBase* term10 = parseExpression(expression10, 0, 1).first;
    string str10 = term10->toString();

    string expression11 = "[3](2x+5y)";
    string expected11 = "[3](2x+5y)";
    TermBase* term11 = parseExpression(expression11, 0, 1).first;
    string str11 = term11->toString();

    string expression12 = "(3xd+[4](2d+5y))";
    string expected12 = "(3xd+[4](2d+5y))";
    TermBase* term12 = parseExpression(expression12, 0, 1).first;
    string str12 = term12->toString();

    string expression13 = "{x/7y}^(4t+6)";
    string expected13 = "{x/7y}^(4t+6)";
    TermBase* term13 = parseExpression(expression13, 0, 1).first;
    string str13 = term13->toString();

    if (expected1 == str1 & expected2 == str2 & expected3 == str3){
        return true;
    }else{
        return false;
    }
}

bool testEquationParse(){
    return false;
}
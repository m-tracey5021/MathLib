#include "../Algebra/eqParser.h"
#include <string>
#include <utility>
#include <iostream>

using namespace std;

bool testExpressionParse(){

    int zeroIndex;

    zeroIndex = 0;    
    string expression1 = "2a";
    string expected1 = "2a";
    TermContainer* term1 = parseExpression(expression1, zeroIndex);
    string str1 = term1->toString();
    
    zeroIndex = 0;
    string expression2 = "3x+{2/xy}";
    string expected2 = "3x+{2/xy}";
    TermContainer* term2 = parseExpression(expression2, zeroIndex);
    string str2 = term2->toString();

    zeroIndex = 0;
    string expression3 = "3x+{2/(xy+5t)}";
    string expected3 = "3x+{2/(xy+5t)}";
    TermContainer* term3 = parseExpression(expression3, zeroIndex);
    string str3 = term3->toString();

    zeroIndex = 0;
    string expression4 = "(3x+5)(2a-6)";
    string expected4 = "(3x+5)(2a-6)";
    TermContainer* term4 = parseExpression(expression4, zeroIndex);
    string str4 = term4->toString();

    zeroIndex = 0;
    string expression5 = "31x+206y";
    string expected5 = "31x+206y";
    TermContainer* term5 = parseExpression(expression5, zeroIndex);
    string str5 = term5->toString();

    zeroIndex = 0;
    string expression6 = "(28x-42y)+(3x+7y)";
    string expected6 = "(28x-42y)+(3x+7y)";
    TermContainer* term6 = parseExpression(expression6, zeroIndex);
    string str6 = term6->toString();

    zeroIndex = 0;
    string expression7 = "{(28x-42y)/(3x+7y)}";
    string expected7 = "{(28x-42y)/(3x+7y)}";
    TermContainer* term7 = parseExpression(expression7, zeroIndex);
    string str7 = term7->toString();

    zeroIndex = 0;
    string expression8 = "x^(2)";
    string expected8 = "x^(2)";
    TermContainer* term8 = parseExpression(expression8, zeroIndex);
    string str8 = term8->toString();

    zeroIndex = 0;
    string expression9 = "(28x-42y)^(23y+8)";
    string expected9 = "(28x-42y)^(23y+8)";
    TermContainer* term9 = parseExpression(expression9, zeroIndex);
    string str9 = term9->toString();

    zeroIndex = 0;
    string expression10 = "[2|x]";
    string expected10 = "[2|x]";
    TermContainer* term10 = parseExpression(expression10, zeroIndex);
    string str10 = term10->toString();

    zeroIndex = 0;
    string expression11 = "[3|(2x+5y)]";
    string expected11 = "[3|(2x+5y)]";
    TermContainer* term11 = parseExpression(expression11, zeroIndex);
    string str11 = term11->toString();

    zeroIndex = 0;
    string expression12 = "3xd+[4|(2d+5y)]";
    string expected12 = "3xd+[4|(2d+5y)]";
    TermContainer* term12 = parseExpression(expression12, zeroIndex);
    string str12 = term12->toString();

    zeroIndex = 0;
    string expression13 = "{x/7y}^(4t+6)";
    string expected13 = "{x/7y}^(4t+6)";
    TermContainer* term13 = parseExpression(expression13, zeroIndex);
    string str13 = term13->toString();

    zeroIndex = 0;
    string expression14 = "4+2t^-(4f+3)";
    string expected14 = "4+2t^-(4f+3)";
    TermContainer* term14 = parseExpression(expression14, zeroIndex);
    string str14 = term14->toString();

    zeroIndex = 0;
    string expression15 = "4+2t^-(4)";
    string expected15 = "4+2t^-(4)";
    TermContainer* term15 = parseExpression(expression15, zeroIndex);
    string str15 = term15->toString();

    zeroIndex = 0;
    string expression16 = "(4+2t)^-(4)";
    string expected16 = "(4+2t)^-(4)";
    TermContainer* term16 = parseExpression(expression16, zeroIndex);
    string str16 = term16->toString();

    if (expected1 == str1 & expected2 == str2 & expected3 == str3){
        return true;
    }else{
        return false;
    }
}

bool testEquationParse(){
    return false;
}

bool testExpand(){
    int zeroIndex;
    
    zeroIndex = 0;
    string expression1 = "6^3";
    string expected1 = "666";
    TermContainer* term1 = parseExpression(expression1, zeroIndex);
    term1->expandExponent();
    string str1 = term1->toString();

    if (str1 == expected1){
        return true;
    }else{
        return false;
    }
}
#include "../Algebra/eqParser.h"
#include <string>
#include <utility>
#include <iostream>

using namespace std;

bool testExpressionParse(){

    string expression0 = "2";
    string expected0 = "2";
    TermBase* term0 = parseExpression(expression0);
    string str0 = term0->toString();
  
    string expression1 = "2a";
    string expected1 = "2a";
    TermBase* term1 = parseExpression(expression1);
    string str1 = term1->toString();
    
    string expression2 = "3x+{2/xy}";
    string expected2 = "3x+{2/xy}";
    TermBase* term2 = parseExpression(expression2);
    string str2 = term2->toString();

    string expression3 = "3x+{2/(xy+5t)}";
    string expected3 = "3x+{2/(xy+5t)}";
    TermBase* term3 = parseExpression(expression3);
    string str3 = term3->toString();

    string expression4 = "(3x+5)(2a-6)";
    string expected4 = "(3x+5)(2a-6)";
    TermBase* term4 = parseExpression(expression4);
    string str4 = term4->toString();

    string expression5 = "31x+206y";
    string expected5 = "31x+206y";
    TermBase* term5 = parseExpression(expression5);
    string str5 = term5->toString();

    string expression6 = "(28x-42y)+(3x+7y)";
    string expected6 = "(28x-42y)+(3x+7y)";
    TermBase* term6 = parseExpression(expression6);
    string str6 = term6->toString();

    string expression7 = "{(28x-42y)/(3x+7y)}";
    string expected7 = "{(28x-42y)/(3x+7y)}";
    TermBase* term7 = parseExpression(expression7);
    string str7 = term7->toString();

    string expression8 = "x^(2)";
    string expected8 = "x^(2)";
    TermBase* term8 = parseExpression(expression8);
    string str8 = term8->toString();

    string expression9 = "(28x-42y)^(23y+8)";
    string expected9 = "(28x-42y)^(23y+8)";
    TermBase* term9 = parseExpression(expression9);
    string str9 = term9->toString();

    string expression10 = "[2|x]";
    string expected10 = "[2|x]";
    TermBase* term10 = parseExpression(expression10);
    string str10 = term10->toString();

    string expression11 = "[3|(2x+5y)]";
    string expected11 = "[3|(2x+5y)]";
    TermBase* term11 = parseExpression(expression11);
    string str11 = term11->toString();

    string expression12 = "3xd+[4|(2d+5y)]";
    string expected12 = "3xd+[4|(2d+5y)]";
    TermBase* term12 = parseExpression(expression12);
    string str12 = term12->toString();

    string expression13 = "{x/7y}^(4t+6)";
    string expected13 = "{x/7y}^(4t+6)";
    TermBase* term13 = parseExpression(expression13);
    string str13 = term13->toString();

    string expression14 = "4+2t^-(4f+3)";
    string expected14 = "4+2t^-(4f+3)";
    TermBase* term14 = parseExpression(expression14);
    string str14 = term14->toString();

    string expression15 = "4+2t^(-4)";
    string expected15 = "4+2t^(-4)";
    TermBase* term15 = parseExpression(expression15);
    string str15 = term15->toString();

    string expression16 = "(4+2t)^(-4)";
    string expected16 = "(4+2t)^(-4)";
    TermBase* term16 = parseExpression(expression16);
    string str16 = term16->toString();

    string expression17 = "(4+2t)^-(4+8y)";
    string expected17 = "(4+2t)^-(4+8y)";
    TermBase* term17 = parseExpression(expression17);
    string str17 = term17->toString();

    string expression18 = "(4+2t)^(-4+8y)";
    string expected18 = "(4+2t)^(-4+8y)";
    TermBase* term18 = parseExpression(expression18);
    string str18 = term18->toString();

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
    
    
    string expression1 = "6^(3)";
    string expected1 = "666";
    TermBase* term1 = parseExpression(expression1);
    TermBase* expanded1 = term1->expandForExponent();
    string str1 = expanded1->toString();

    string expression2 = "6^(x+y)";
    string expected2 = "6^(x)6^(y)";
    TermBase* term2 = parseExpression(expression2);
    TermBase* expanded2 = term2->expandForExponent();
    string str2 = expanded2->toString();

    string expression3 = "x^(2z+3y)";
    string expected3 = "x^(z)x^(z)x^(y)x^(y)x^(y)";
    TermBase* term3 = parseExpression(expression3);
    TermBase* expanded3 = term3->expandForExponent();
    string str3 = expanded3->toString();
    
    string expression4 = "x^(2z^(2)+3y)";
    string expected4 = "x^(zz)x^(zz)x^(y)x^(y)x^(y)";
    TermBase* term4 = parseExpression(expression4);
    TermBase* expanded4 = term4->expandForExponent();
    string str4 = expanded4->toString();

    std::vector<TermBase*> factors4 = term4->getAllFactors();

    string expression5 = "12^(4xy-3)";
    string expected5 = "12^(xy)12^(xy)12^(xy)12^(xy)12^(-3)";
    TermBase* term5 = parseExpression(expression5);
    TermBase* expanded5 = term5->expandForExponent();
    string str5 = expanded5->toString();

    std::vector<TermBase*> factors5 = term5->getAllFactors();

    string expression6 = "x^({6/10})";
    string expected6 = "x^({1/10})x^({1/10})x^({1/10})x^({1/10})x^({1/10})x^({1/10})";
    TermBase* term6 = parseExpression(expression6);
    TermBase* expanded6 = term6->expandForExponent();
    string str6 = expanded6->toString();

    std::vector<TermBase*> factors6= term6->getAllFactors();

    string expression7 = "x^(6(2x+7y))";
    string expected7_1 = "x^(2x+7y)x^(2x+7y)x^(2x+7y)x^(2x+7y)x^(2x+7y)x^(2x+7y)";
    string expected7_2 = "x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)";
    TermBase* term7 = parseExpression(expression7);
    TermBase* expanded7 = term7->expandForExponent();
    string str7 = expanded7->toString();

    std::vector<TermBase*> factors7= term7->getAllFactors();
    

    /*
    if (str1 == expected1){
        return true;
    }else{
        return false;
    }
    */
   return false;
}
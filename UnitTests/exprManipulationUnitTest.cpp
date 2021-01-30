#include <string>
#include "../Algebra/eqParser.h"

bool testEquality(){

    std::vector<std::string> expressions1 = {"2a+8", "7(x^(2x)+14)", "6x+(3y+7)(4+t)", "x+{2/(6t+xy)}", "2x"};
    std::vector<std::string> expressions2 = {"2a+8", "7(x^(2x)+14)", "6x+(3y+7)(4+t)", "x+{2/(7t+xy)}", "2y"};
    std::vector<TermBase*> terms1;
    std::vector<TermBase*> terms2;

    std::vector<bool> results = {0, 0, 0, 0, 0};

    for (int i = 0; i < expressions1.size(); i ++){
        TermBase* term1 = parseExpression(expressions1[i]);
        TermBase* term2 = parseExpression(expressions2[i]);
        terms1.push_back(term1);
        terms2.push_back(term2);
    }

    for (int i = 0; i < terms1.size(); i ++){
        results[i] = terms1[i]->isEqual(terms2[i]);
    }

    if (results[0] & results[1] & results[2] & !results[3] & !results[4]){
        return true;
    }else{
        return false;
    }
}

bool testExpand(){
    
    std::vector<std::string> expressions = {"6^(3)", "6^(x+y)", "x^(2z+3y)", 
                                            "x^(2z^(2)+3y)", "12^(4xy-3)", "x^({6/10})",
                                            "x^(6(2x+7y))", "3^((2t)^3)"};
    std::vector<std::string> expectedStrings = {"216", "6^(x)6^(y)", "x^(z)x^(z)x^(y)x^(y)x^(y)",
                                                "x^(zz)x^(zz)x^(y)x^(y)x^(y)", "12^(xy)12^(xy)12^(xy)12^(xy){1/12}{1/12}{1/12}", 
                                                "x^({1/10})x^({1/10})x^({1/10})x^({1/10})x^({1/10})x^({1/10})", 
                                                "x^(x)x^(x)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(x)x^(x)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(x)x^(x)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(x)x^(x)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(x)x^(x)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(x)x^(x)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)x^(y)",
                                                "3^(ttt)3^(ttt)3^(ttt)3^(ttt)3^(ttt)3^(ttt)"};

    std::vector<bool> results = {0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < expressions.size(); i ++){
        std::string expression = expressions[i];
        std::string expanded = parseExpression(expression)->expandForExponent()->toString();
        expanded == expectedStrings[i] ? results[i] = 1 : results[i] = 0;
    }

    for (bool r : results){
        if (!r){
            return false;
        }
    }
    return true;

    // string expression1 = "6^(3)";
    // string expected1 = "666";
    // TermBase* term1 = parseExpression(expression1);
    // TermBase* expanded1 = term1->expandForExponent();
    // string str1 = expanded1->toString();

    // string expression2 = "6^(x+y)";
    // string expected2 = "6^(x)6^(y)";
    // TermBase* term2 = parseExpression(expression2);
    // TermBase* expanded2 = term2->expandForExponent();
    // string str2 = expanded2->toString();

    // string expression3 = "x^(2z+3y)";
    // string expected3 = "x^(z)x^(z)x^(y)x^(y)x^(y)";
    // TermBase* term3 = parseExpression(expression3);
    // TermBase* expanded3 = term3->expandForExponent();
    // string str3 = expanded3->toString();
    
    // string expression4 = "x^(2z^(2)+3y)";
    // string expected4 = "x^(zz)x^(zz)x^(y)x^(y)x^(y)";
    // TermBase* term4 = parseExpression(expression4);
    // TermBase* expanded4 = term4->expandForExponent();
    // string str4 = expanded4->toString();

    // string expression5 = "12^(4xy-3)";
    // string expected5 = "12^(xy)12^(xy)12^(xy)12^(xy)12^(-3)";
    // TermBase* term5 = parseExpression(expression5);
    // TermBase* expanded5 = term5->expandForExponent();
    // string str5 = expanded5->toString();    

    // string expression6 = "x^({6/10})";
    // string expected6 = "x^({1/10})x^({1/10})x^({1/10})x^({1/10})x^({1/10})x^({1/10})";
    // TermBase* term6 = parseExpression(expression6);
    // TermBase* expanded6 = term6->expandForExponent();
    // string str6 = expanded6->toString();

    // string expression7 = "x^(6(2x+7y))";
    // string expected7_1 = "x^(2x+7y)x^(2x+7y)x^(2x+7y)x^(2x+7y)x^(2x+7y)x^(2x+7y)";
    // string expected7_2 = "x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)x^(xx)x^(yyyyyyy)";
    // TermBase* term7 = parseExpression(expression7);
    // TermBase* expanded7 = term7->expandForExponent();
    // string str7 = expanded7->toString();

    // std::vector<TermBase*> factors4 = term4->getAllFactors();

    // std::vector<TermBase*> factors5 = term5->getAllFactors();

    // std::vector<TermBase*> factors6= term6->getAllFactors();

    // std::vector<TermBase*> factors7= term7->getAllFactors();
    

    
    // if (str1 == expected1){
    //     return true;
    // }else{
    //     return false;
    // }
    
    // return false;
}
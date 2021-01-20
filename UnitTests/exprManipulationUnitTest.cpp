#include <string>
#include "../Algebra/eqParser.h"

bool testEquality(){

    std::string expression0_1 = "2a+8";
    std::string expression0_2 = "2a+8";
    TermBase* term0_1 = parseExpression(expression0_1);
    TermBase* term0_2 = parseExpression(expression0_2);
    bool equal0 = term0_1 == term0_2;

    std::string expression1_1 = "7(x^(2x)+14)";
    std::string expression1_2 = "7(x^(2x)+14)";
    TermBase* term1_1 = parseExpression(expression1_1);
    TermBase* term1_2 = parseExpression(expression1_2);
    bool equal1 = term1_1 == term1_2;

    std::string expression2_1 = "6x+(3y+7)(4+t)";
    std::string expression2_2 = "6x+(3y+7)(4+t)";
    TermBase* term2_1 = parseExpression(expression2_1);
    TermBase* term2_2 = parseExpression(expression2_2);
    bool equal2 = term2_1 == term2_2;

    std::string expression3_1 = "x+{2/(6t+xy)}";
    std::string expression3_2 = "x+{2/(6t+xy)}";
    TermBase* term3_1 = parseExpression(expression3_1);
    TermBase* term3_2 = parseExpression(expression3_2);
    bool equal3 = term3_1 == term3_2;

    if (equal0 & equal1 & equal2 & equal3){
        return true;
    }else{
        return false;
    }
}
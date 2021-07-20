// #include <string>
// #include "../Parsing/mParser.h"

// // bool testEquality(){

// //     std::vector<std::string> expressions1 = {"2a+8", "7(x^(2x)+14)", "6x+(3y+7)(4+t)", "x+{2/(6t+xy)}", "2x"};
// //     std::vector<std::string> expressions2 = {"2a+8", "7(x^(2x)+14)", "6x+(3y+7)(4+t)", "x+{2/(7t+xy)}", "2y"};
// //     std::vector<TermBase*> terms1;
// //     std::vector<TermBase*> terms2;

// //     std::vector<bool> results = {0, 0, 0, 0, 0};

// //     for (int i = 0; i < expressions1.size(); i ++){
// //         TermBase* term1 = parseExpression(expressions1[i]);
// //         TermBase* term2 = parseExpression(expressions2[i]);
// //         terms1.push_back(term1);
// //         terms2.push_back(term2);
// //     }

// //     for (int i = 0; i < terms1.size(); i ++){
// //         results[i] = terms1[i]->isEqual(terms2[i]);
// //     }

// //     if (results[0] & results[1] & results[2] & !results[3] & !results[4]){
// //         return true;
// //     }else{
// //         return false;
// //     }
// // }

// bool testExpand(){
    
//     MParser parser;
//     vector<string> expressions = {
//         // "c^{2}",
//         // "x+t^{2}",
//         // "(x+t)^{2}",
//         // "2x(y^{2})",
//         // "2((xy)^{2})",
//         // "xy^{2t}z",
//         // "xy^{2+t}z",
//         // "xy^{2/t}z",
//         // "(xy)^{2x}z",
//         "x^{2^{3}}",
//         "x^{2x^{3}}",
//         "x^{(2x)^{3}}",
//         "(x^{2})^{3}",
//         "(2x+t)^{3x^{4r-2t}}"
//     };

//     for (string exp : expressions){
//         parser.parseExpression(exp);
//         shared_ptr<Expression> expression = parser.getParseTree();
//         string parsedExpressionStr = expression->toString();
//         string parseTreeStr = expression->toString(4);
//         std::cout << "===== compact =====" << std::endl << std::endl;
//         std::cout << parsedExpressionStr << std::endl << std::endl;
//         std::cout << parseTreeStr << std::endl << std::endl;
//         std::cout << "===== compact =====" << std::endl << std::endl;


//         shared_ptr<Symbol> theThree = expression->getRoot()->getChildren()[1]->getChildren()[1];
//         // shared_ptr<Symbol> null;
//         shared_ptr<Symbol> theSecondExp = theThree->getParent(); // getParent(theThree.get(), null, expression->getRoot());


//         // Expression expanded = expression->expandExponents();
//         expression->expandExponents();
//         string expandedExpressionStr = expression->toString();
//         string expandedTreeStr = expression->toString(4);
//         std::cout << "===== expanded =====" << std::endl << std::endl;
//         std::cout << expandedExpressionStr << std::endl << std::endl;
//         std::cout << expandedTreeStr << std::endl << std::endl;
//         std::cout << "===== expanded =====" << std::endl << std::endl;
//         int x = 0;
//     }
// }

// bool testAppend(){
//     MParser parser;
//     vector<pair<string, string>> expressions = {

//         {"xyz", "abc"}
//     };

//     for (pair<string, string> exp : expressions){
//         parser.parseExpression(exp.first);
//         shared_ptr<Expression> expression1 = parser.getParseTree();

//         parser.parseExpression(exp.second);
//         shared_ptr<Expression> expression2 = parser.getParseTree();
        
//         expression1->getRoot()->appendChild(expression2->getRoot());

//         std::cout << expression1->toString(4) << std::endl;
//     }
// }

// bool testEvaluate(){
//     MParser parser;
//     vector<string> expressions = {
//         "4+2+3",
//         "4+2+3+x",
//         "4+2+3+(x+6)",
//         "4+2+3+(6+7)",
//         "4-2-3",
//         "4+2+3-1",
//         "4+(2-x)",
//         "-4+2",
//         "4-2+7(1+2)",
//         "4/2",
//         "4/(1+1)",
//         "x+x",
//         "x^{2+3}",
//         "x^{2+10/5}"
//     };
//     for (string exp : expressions){
//         parser.parseExpression(exp);
//         shared_ptr<Expression> expression = parser.getParseTree();

//         shared_ptr<Symbol> result = expression->getRoot()->evaluate();

//         // std::cout << result->toString(false) << std::endl;

//         std::cout << result->toString(4) << std::endl;
        
//     }
// }

// bool testEvaluateConstants(){
//     MParser parser;
//     vector<string> expressions = {
//         // "4+2+3",
//         // "4+2+3+x",
//         // "4+2+3+(x+6)",
//         // "4+2+3+(6+7)",
//         // "4-2-3",
//         // "4+2+3-1",
//         // "4+(2-x)",
//         // "-4+2",
//         // "4-2+7(1+2)",
//         // "4/2",
//         // "4/(1+1)",
//         "x+x",
//         "x^{2+3}",
//         "x^{2+10/5}"
//     };
//     for (string exp : expressions){
//         parser.parseExpression(exp);
//         shared_ptr<Expression> expression = parser.getParseTree();

//         expression->getRoot()->evaluateConstants();

//         std::cout << expression->toString() << std::endl;

//         std::cout << expression->toString(4) << std::endl;
        
//     }
// }

// bool testLikeTerms(){
//     MParser parser;
//     vector<string> expressions = {
//         "2x+3x",
//         "2xy-4xy",
//         "3x^{2}+9x^{2}"
//     };
//     for (string exp : expressions){
//         parser.parseExpression(exp);
//         shared_ptr<Expression> expression = parser.getParseTree();

//         expression->getRoot()->evaluateConstants();

//         std::cout << expression->toString() << std::endl;

//         std::cout << expression->toString(4) << std::endl;
        
//     }
// }
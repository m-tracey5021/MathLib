// #include "expressionFactory.h"

// ExpressionFactory::ExpressionFactory(): tmpSign(true), tmpConstant(1), tmpVariable('_'){}

// ExpressionPtr ExpressionFactory::get(){
//     return move(expression);
// }

// void ExpressionFactory::reset(){
//     tmpSign = true;
//     tmpRoot.reset();
//     tmpExponent.reset();
//     tmpOperands.clear();
//     tmpNumerator.reset();
//     tmpDenominator.reset();
//     tmpConstant = 1;
//     tmpVariable = '_';
// }

// // ExpressionFactory ExpressionFactory::moveSummation(){
// //     expression = make_unique<Summation>(tmpSign, tmpRoot, tmpExponent, tmpOperands); 
// //     return move(*this);
// // }

// // ExpressionFactory ExpressionFactory::moveMultiplication(){
// //     expression = make_unique<Multiplication>(tmpSign, tmpRoot, tmpExponent, tmpOperands); 
// //     return move(*this);
// // }

// // ExpressionFactory ExpressionFactory::moveDivision(){
// //     expression = make_unique<Division>(tmpSign, tmpRoot, tmpExponent, tmpNumerator, tmpDenominator); 
// //     return move(*this);
// // }

// // ExpressionFactory ExpressionFactory::moveConstantExpression(){
// //     expression = make_unique<ConstantExpression>(tmpSign, tmpRoot, tmpExponent, tmpConstant);
// //     return move(*this);
// // }

// // ExpressionFactory ExpressionFactory::moveVariableExpression(){
// //     expression = make_unique<VariableExpression>(tmpSign, tmpRoot, tmpExponent, tmpVariable);
// //     return move(*this);
// // }

// ExpressionFactory ExpressionFactory::buildSummation(){
//     // Expression* rootPtr = tmpRoot.get();
//     // Expression* exponentPtr = tmpExponent.get();
//     // ExpressionPtr root = ExpressionPtr(rootPtr);
//     // ExpressionPtr exponent = ExpressionPtr(exponentPtr);
//     // vector<ExpressionPtr> operands;
//     // for(int i = 0; i < tmpOperands.size(); i ++){
//     //     ExpressionPtr toCopy = move(tmpOperands[i]);
//     //     Expression* toCopyPtr = toCopy.get();
//     //     ExpressionPtr copied = ExpressionPtr(toCopyPtr);
//     //     operands.push_back(move(copied));
//     // }
//     expression = make_unique<Summation>(tmpSign, tmpRoot, tmpExponent, tmpOperands); 
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::buildMultiplication(){
//     // Expression* rootPtr = tmpRoot.get();
//     // Expression* exponentPtr = tmpExponent.get();
//     // ExpressionPtr root = ExpressionPtr(rootPtr);
//     // ExpressionPtr exponent = ExpressionPtr(exponentPtr);
//     // vector<ExpressionPtr> operands;
//     // for(int i = 0; i < tmpOperands.size(); i ++){
//     //     ExpressionPtr toCopy = move(tmpOperands[i]);
//     //     Expression* toCopyPtr = toCopy.get();
//     //     ExpressionPtr copied = ExpressionPtr(toCopyPtr);
//     //     operands.push_back(move(copied));
//     // }
//     expression = make_unique<Multiplication>(tmpSign, tmpRoot, tmpExponent, tmpOperands); 
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::buildDivision(){
//     // Expression* rootPtr = tmpRoot.get();
//     // Expression* exponentPtr = tmpExponent.get();
//     // Expression* numeratorPtr = tmpNumerator.get();
//     // Expression* denominatorPtr = tmpDenominator.get();
//     // ExpressionPtr root = ExpressionPtr(rootPtr);
//     // ExpressionPtr exponent = ExpressionPtr(exponentPtr);
//     // ExpressionPtr numerator = ExpressionPtr(numeratorPtr);
//     // ExpressionPtr denominator = ExpressionPtr(denominatorPtr);
//     expression = make_unique<Division>(tmpSign, tmpRoot, tmpExponent, tmpNumerator, tmpDenominator); 
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::buildConstantExpression(){
//     // Expression* rootPtr = tmpRoot.get();
//     // Expression* exponentPtr = tmpExponent.get();
//     // ExpressionPtr root = ExpressionPtr(rootPtr);
//     // ExpressionPtr exponent = ExpressionPtr(exponentPtr);
//     expression = make_unique<ConstantExpression>(tmpSign, tmpExponent, tmpExponent, tmpConstant);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::buildVariableExpression(){
//     // Expression* rootPtr = tmpRoot.get();
//     // Expression* exponentPtr = tmpExponent.get();
//     // ExpressionPtr root = ExpressionPtr(rootPtr);
//     // ExpressionPtr exponent = ExpressionPtr(exponentPtr);
//     expression = make_unique<VariableExpression>(tmpSign, tmpRoot, tmpExponent, tmpVariable);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::sign(bool s){
//     tmpSign = s;
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::root(Expression& r){
//     ExpressionPtr tmp = ExpressionPtr (&r);
//     tmpRoot = move(tmp);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::root(ExpressionPtr& r){
//     tmpRoot = move(r);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::root(ExpressionPtr&& r){
//     tmpRoot = move(r);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::exponent(Expression& e){
//     ExpressionPtr tmp = ExpressionPtr (&e);
//     tmpExponent = move(tmp);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::exponent(ExpressionPtr& e){
//     tmpExponent = move(e);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::exponent(ExpressionPtr&& e){
//     tmpExponent = move(e);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::operands(vector<ExpressionPtr>& o){
//     tmpOperands = move(o);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::numerator(Expression& n){
//     ExpressionPtr tmp = ExpressionPtr(&n);
//     tmpNumerator = move(tmp);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::numerator(ExpressionPtr& n){
//     tmpNumerator = move(n);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::numerator(ExpressionPtr&& n){
//     tmpNumerator = move(n);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::denominator(Expression& d){
//     ExpressionPtr tmp = ExpressionPtr(&d);
//     tmpDenominator = move(tmp);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::denominator(ExpressionPtr& d){
//     tmpDenominator = move(d);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::denominator(ExpressionPtr&& d){
//     tmpDenominator = move(d);
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::constant(int c){
//     tmpConstant = c;
//     return move(*this);
// }

// ExpressionFactory ExpressionFactory::variable(char v){
//     tmpVariable = v;
//     return move(*this);
// }
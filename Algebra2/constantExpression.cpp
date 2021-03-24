// #include "expression.h"
// #include "expressionFactory.h"

// ConstantExpression::ConstantExpression(): Expression(){}

// ConstantExpression::ConstantExpression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, int constant): Expression(sign, root, exponent), constant(constant){}

// // ConstantExpression::~ConstantExpression(){
// //     root.reset();
// //     exponent.reset();
// //     parentExpression.reset();
// //     delete &root;
// //     delete &exponent;
// //     delete &parentExpression;
// // }

// int ConstantExpression::getConstant(){
//     return constant;
// }

// void ConstantExpression::setConstant(int c){
//     constant = c;
// }

// IntPtr ConstantExpression::getValue(){
//     IntPtr toRet = IntPtr(&constant);
//     return toRet;
// }

// vector<ExpressionPtr> ConstantExpression::getContent(){
//     ExpressionPtr thisPtr  = CEPtr(this);
//     vector<ExpressionPtr> content;
//     content.push_back(move(thisPtr));
//     return content;
// }

// void ConstantExpression::appendExpression(Expression& e){}

// void ConstantExpression::removeExpression(int i){}

// void ConstantExpression::replaceExpression(int i, Expression& e){}

// void ConstantExpression::sanitise(){}

// bool ConstantExpression::isEqual(Expression& other){return other.isEqual(*this);}

// bool ConstantExpression::isEqual(Summation& other){return false;}

// bool ConstantExpression::isEqual(Multiplication& other){return false;}

// bool ConstantExpression::isEqual(Division& other){return false;}

// bool ConstantExpression::isEqual(ConstantExpression& other){
//     if (other.getConstant() == constant){
//         return true;
//     }else{
//         return false;
//     }
// }

// bool ConstantExpression::isEqual(VariableExpression& other){return false;}

// bool ConstantExpression::isOne(){
//     if (constant == 1){
//         return true;
//     }else{
//         return false;
//     }
// }

// bool ConstantExpression::isAtomic(){
//     return true;
// }

// bool ConstantExpression::isAtomicExponent(){
//     if (constant == 1){
//         return true;
//     }else{
//         return false;;
//     }
// }

// bool ConstantExpression::isAtomicNumerator(){
//     if (constant == 1){
//         return true;
//     }else{
//         return false;;
//     }
// }

// bool ConstantExpression::isLikeExpression(Expression& other){
//     return false;
// }

// bool ConstantExpression::isMergeable(){
//     return true;
// }

// ExpressionPtr ConstantExpression::sum(Summation& s){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::sum(Multiplication& m){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::sum(Division& d){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::sum(ConstantExpression& ce){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::sum(VariableExpression& ve){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::multiply(Summation& m){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::multiply(Multiplication& m){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::multiply(Division& d){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::multiply(ConstantExpression& ce){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::multiply(VariableExpression& ve){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::divide(Summation& m){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::divide(Multiplication& m){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::divide(Division& d){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::divide(ConstantExpression& ce){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::divide(VariableExpression& ve){
//     return nullptr;
// }

// ExpressionPtr ConstantExpression::mergeMultiplications(Expression& other){
//     ExpressionFactory factory;
//     if (other.isMergeable()){

//         vector<ExpressionPtr> tmpTerms;
//         tmpTerms.push_back(move(ExpressionPtr (this)));

//         vector<ExpressionPtr> otherTerms = other.getContent();
//         for (int j = 0; j < otherTerms.size(); j ++){
//             tmpTerms.push_back(move(otherTerms[j]));
//         }
//         // ExpressionPtr emptyRoot = ExpressionPtr();
//         // ExpressionPtr emptyExponent = ExpressionPtr();
        
//         return factory.sign(true).root(nullptr).exponent(nullptr).operands(tmpTerms).buildMultiplication().get();
//         //return make_unique<Multiplication>(true, nullptr, nullptr, tmpTerms);
//     }else{
//         return factory.buildMultiplication().get();
//     }
// }

// // ExpressionPtr ConstantExpression::sum(Summation s){
// //     // ExpressionPtr() ConstantExpressionPtr (new ConstantExpression(true, ExpressionPtr(), ExpressionPtr(), 1));
// //     // return ConstantExpressionPtr;
// //     return ExpressionPtr();
// // }

// // ExpressionPtr ConstantExpression::sum(Multiplication m){
// //     ExpressionPtr ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
// //     return ConstantExpressionPtr;
// // }

// // ExpressionPtr ConstantExpression::sum(Division d){
// //     ExpressionPtr ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
// //     return ConstantExpressionPtr;
// // }

// // ExpressionPtr ConstantExpression::sum(ConstantExpression c){
// //     ExpressionPtr ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
// //     return ConstantExpressionPtr;
// // }

// // ExpressionPtr ConstantExpression::sum(VariableExpression v){
// //     ExpressionPtr ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
// //     return ConstantExpressionPtr;
// // }

// ExpressionPtr ConstantExpression::expandForExponent(){
//     if (!exponent){
//         return ExpressionPtr (this);
//     }else{
//         ExpressionPtr expanded = exponent->expandAsExponent(*this);
//         expanded->sanitise();
//         return expanded;
//     }
// }

// ExpressionPtr ConstantExpression::expandAsExponent(Expression& baseExpression){
//     ExpressionFactory factory;
//     ExpressionPtr expandedTerm = factory.buildMultiplication().get();

//     if (!sign){
//         expandedTerm = expandAsNegativeExponent(baseExpression);
//         return expandedTerm;
//     }else{
//         if (constant > 1){
//             for (int i = 0; i < constant; i ++){
//                 ExpressionPtr copiedBase = baseExpression.copy();
//                 ExpressionPtr emptyExponent = ExpressionPtr();
//                 copiedBase->setExponent(emptyExponent);
//                 expandedTerm->appendExpression(*copiedBase);
//             }
//             return expandedTerm;
//         }else{
//             return ExpressionPtr (this);
//         }
//     }
// }

// ExpressionPtr ConstantExpression::expandAsConstNum(Expression& baseExpression, Expression& baseDivision){
//     ExpressionFactory factory;
//     ExpressionPtr expandedTerm = factory.buildMultiplication().get();
//     factory.reset();
//     ExpressionPtr numerator = factory.buildConstantExpression().get();
//     factory.reset();
//     ExpressionPtr denominator = baseDivision.getContent()[1]->copy();

//     // emptyRoot = ExpressionPtr();
//     // emptyExponent = ExpressionPtr();
//     ExpressionPtr newExponent = factory.sign(true).root(nullptr).exponent(nullptr).numerator(numerator).denominator(denominator).buildDivision().get();
//     //ExpressionPtr newExponent = make_unique<Division>(true, nullptr, nullptr, numerator, denominator);
//     ExpressionPtr newTerm = baseExpression.copy();
//     newTerm->setExponent(newExponent);


//     for (int i = 0; i < constant; i ++){
//         expandedTerm->appendExpression(*newTerm);
//     }

//     return expandedTerm;
// }

// ExpressionPtr ConstantExpression::expandAsNegativeExponent(Expression& baseExpression){
//     ExpressionFactory factory;
//     ExpressionPtr expandedTerm = factory.buildMultiplication().get();
//     factory.reset();

//     for (int i = 0; i < constant; i ++){
//         ExpressionPtr newNum = factory.buildConstantExpression().get();
//         factory.reset();
//         //ExpressionPtr newNum = make_unique<ConstantExpression>(true, nullptr, nullptr, 1);
//         ExpressionPtr newDenom = baseExpression.copy();
//         ExpressionPtr empty = ExpressionPtr();
//         newDenom->setExponent(empty);
        
//         ExpressionPtr newRational = factory.numerator(newNum).denominator(newDenom).buildDivision().get();
//         // ExpressionPtr newRational = make_unique<Division>(true, 
//         //                                                  nullptr, 
//         //                                                  nullptr, 
//         //                                                  move(newNum), 
//         //                                                  move(newDenom));

//         expandedTerm->appendExpression(*newRational);
//     }
//     return expandedTerm;
// }

// ExpressionPtr ConstantExpression::factor(){
//     return ExpressionPtr (this);
// }

// vector<ExpressionPtr> ConstantExpression::getConstantFactors(){
//     ExpressionFactory factory;
//     vector<ExpressionPtr> constantFactors;
//     for (int i = 1; i <= constant; i ++){
//         if (constant % i == 0){
//             ExpressionPtr factor = factory.constant(i).buildConstantExpression().get();
//             constantFactors.push_back(move(factor));
//         }
//     }
//     return constantFactors;
// }

// vector<ExpressionPtr> ConstantExpression::getAllFactors(){

//     vector<ExpressionPtr> factors;
//     vector<ExpressionPtr> constantFactors = getConstantFactors();

//     ExpressionPtr expanded = expandForExponent();
//     vector<ExpressionPtr> expandedTerms = expanded->getContent();
//     getAllSubTerms(expandedTerms, factors, 0, 0);

//     for (ExpressionPtr& cf : constantFactors){
//         factors.push_back(move(cf));
//     }
//     return factors;
// }

// ExpressionPtr ConstantExpression::copy(){
//     ExpressionFactory factory;
//     if (root != nullptr & exponent != nullptr){        
//         return factory.sign(sign).root(root->copy()).exponent(exponent->copy()).constant(constant).buildConstantExpression().get(); 
//     }else if (root == nullptr & exponent != nullptr){
//         return factory.sign(sign).root(nullptr).exponent(exponent->copy()).constant(constant).buildConstantExpression().get();
//     }else if (root != nullptr & exponent == nullptr){
//         return factory.sign(sign).root(root->copy()).exponent(nullptr).constant(constant).buildConstantExpression().get();
//     }else{
//         return factory.sign(sign).root(nullptr).exponent(nullptr).constant(constant).buildConstantExpression().get();
//     } 
    
// }

// string ConstantExpression::toString(){
//     string expressionString = "";
//     if (!sign){
//         expressionString += '-';
//     }

//     expressionString += std::to_string(constant);

//     if (root != nullptr){
//         if (!root->isOne()){
//             expressionString = '[' + root->toString() + '|' + expressionString + ']';
//         }
//     }
//     if (exponent != nullptr){
//         if (!exponent->isOne()){
//             expressionString = expressionString + exponent->exponentToString();
//         }
//     }
//     return expressionString;
// }

// string ConstantExpression::exponentToString(){
//     return "^(" + this->toString() + ')';
// }
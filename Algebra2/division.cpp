// #include "expression.h"
// #include "expressionFactory.h"

// Division::Division(){}

// Division::Division(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, ExpressionPtr& numerator, ExpressionPtr& denominator):
//                         Expression(sign, root, exponent), 
//                         numerator(move(numerator)), 
//                         denominator(move(denominator)){}

// ExpressionPtr Division::getNumerator(){
//     return move(numerator);
// }

// ExpressionPtr Division::getDenominator(){
//     return move(denominator);
// }

// void Division::setNumerator(ExpressionPtr& n){
//     numerator = move(n);
// }

// void Division::setDenominator(ExpressionPtr& d){
//     denominator = move(d);
// }

// IntPtr Division::getValue(){
//     IntPtr empty = IntPtr();
//     return empty;
// }

// vector<ExpressionPtr> Division::getContent(){
//     vector<ExpressionPtr> content;
//     content.push_back(move(numerator));
//     content.push_back(move(denominator));
//     return content;
// }

// void Division::appendExpression(Expression& e){
//     ExpressionPtr toAppend = ExpressionPtr(&e);
//     if (numerator == nullptr & denominator == nullptr){
//         numerator = move(toAppend);
//     }else if (numerator != nullptr & denominator == nullptr){
//         denominator = move(toAppend);
//     }else{
//         // throw error
//     }
// }

// void Division::removeExpression(int i){
//     if (i < 2){
//         if (i == 0){
//             numerator = nullptr;
//         }else{
//             denominator = nullptr;
//         }
//     }else{
//         // throw error
//     }
// }

// void Division::replaceExpression(int i, Expression& e){
//     if (i < 2){
//         ExpressionPtr toAppend = ExpressionPtr(&e);
//         if (i == 0){
//             numerator = move(toAppend);
//         }else{
//             denominator = move(toAppend);
//         }
//     }else{
//         // throw error
//     }
// }

// void Division::sanitise(){}

// bool Division::isEqual(Expression& other){return other.isEqual(*this);}

// bool Division::isEqual(Summation& other){return false;}

// bool Division::isEqual(Multiplication& other){return false;}

// bool Division::isEqual(Division& other){
//     if (numerator->isEqual(*other.getNumerator()) & denominator->isEqual(*other.getDenominator())){
//         return true;
//     }else{
//         return false;
//     }
// }

// bool Division::isEqual(ConstantExpression& other){return false;}

// bool Division::isEqual(VariableExpression& other){return false;}

// bool Division::isOne(){
//     if (numerator->isEqual(*denominator)){
//         return true;
//     }else{
//         return false;
//     }
// }

// bool Division::isAtomic(){return false;}

// bool Division::isAtomicExponent(){
//     if (numerator->isAtomicExponent()){
//         return true;
//     }else{
//         return false;
//     }
// }

// bool Division::isAtomicNumerator(){return false;}

// bool Division::isLikeExpression(Expression& e){return false;}

// bool Division::isMergeable(){return false;}

// ExpressionPtr Division::sum(Summation& s){
//     return nullptr;
// }

// ExpressionPtr Division::sum(Multiplication& m){
//     return nullptr;
// }

// ExpressionPtr Division::sum(Division& d){
//     return nullptr;
// }

// ExpressionPtr Division::sum(ConstantExpression& ce){
//     return nullptr;
// }

// ExpressionPtr Division::sum(VariableExpression& ve){
//     return nullptr;
// }

// ExpressionPtr Division::multiply(Summation& m){
//     return nullptr;
// }

// ExpressionPtr Division::multiply(Multiplication& m){
//     return nullptr;
// }

// ExpressionPtr Division::multiply(Division& d){
//     return nullptr;
// }

// ExpressionPtr Division::multiply(ConstantExpression& ce){
//     return nullptr;
// }

// ExpressionPtr Division::multiply(VariableExpression& ve){
//     return nullptr;
// }

// ExpressionPtr Division::divide(Summation& m){
//     return nullptr;
// }

// ExpressionPtr Division::divide(Multiplication& m){
//     return nullptr;
// }

// ExpressionPtr Division::divide(Division& d){
//     return nullptr;
// }

// ExpressionPtr Division::divide(ConstantExpression& ce){
//     return nullptr;
// }

// ExpressionPtr Division::divide(VariableExpression& ve){
//     return nullptr;
// }

// ExpressionPtr Division::mergeMultiplications(Expression& other){
//     return ExpressionPtr(&other);
// }

// ExpressionPtr Division::expandForExponent(){
//     if (!exponent){
//         return ExpressionPtr(this);
//     }else{
//         ExpressionPtr expanded = exponent->expandAsExponent(*this);
//         expanded->sanitise();
//         return expanded;
//     }
// }

// ExpressionPtr Division::expandAsExponent(Expression& baseExpression){

//     ExpressionPtr expanded = make_unique<Multiplication>();

//     // expand the exponents of the innerTerms

//     ExpressionPtr copied = this->copy();
//     vector<ExpressionPtr> copiedContent = copied->getContent();

//     for (int i = 0; i < copiedContent.size(); i ++){
//         ExpressionPtr innerTerm = move(copiedContent[i]);
//         ExpressionPtr innerExponent = innerTerm->getExponent();
//         if (innerExponent != nullptr){
//             if (!innerExponent->isAtomicExponent()){
//                 ExpressionPtr expandedInnerTerm = innerTerm->expandForExponent();
//                 copied->replaceExpression(i, *expandedInnerTerm);
//             }
//         }
//     }
    
//     // expand the exponent of the main exponent

//     if (copied->getExponent() != nullptr){  
//         copied = move(copied->expandForExponent());
//     }
//     copiedContent = copied->getContent();

//     // expand the main exponent over the baseTerm passed in

//     if (!sign){
//         expanded = move(expandAsNegativeExponent(baseExpression));
//     }else{
//         if (isAtomicExponent()){
//             return ExpressionPtr(&baseExpression);
//         }else if (isAtomic() & !isAtomicExponent()){
//             expanded = move(expandAsExponent(baseExpression));
//         }else{
//             expanded = move(numerator->expandAsConstNum(baseExpression, *copied));

//         }
//     }
    

//     /* 
//         check that the resultant expandedTerm is fully expanded, i.e. all
//         of the exponents are in atomic form, either 1 or n or nm or 1/n 
//     */

//     if (expanded->getContent().size() == 0){
//         return ExpressionPtr(this);
//     }else{
//         for (int i = 0; i < expanded->getContent().size(); i ++){
//             ExpressionPtr ithExpandedTerm = move(expanded->getContent()[i]);
//             ExpressionPtr toReplace = ithExpandedTerm->expandForExponent();
//             expanded->replaceExpression(i, *toReplace); // this is very inefficient
//         }
//         return expanded;
//     }
// }

// ExpressionPtr Division::expandAsConstNum(Expression& baseExpression, Expression& baseDivision){
//     return ExpressionPtr(&baseExpression);
// }

// ExpressionPtr Division::expandAsNegativeExponent(Expression& baseExpression){
//     return ExpressionPtr(&baseExpression);
// }

// ExpressionPtr Division::factor(){
//     return nullptr;
// }

// vector<ExpressionPtr> Division::getConstantFactors(){
//     vector<ExpressionPtr> dummy;
//     return dummy;
// }

// vector<ExpressionPtr> Division::getAllFactors(){
//     vector<ExpressionPtr> dummy;
//     return dummy;
// }

// ExpressionPtr Division::copy(){
//     ExpressionFactory factory;
//     if (root != nullptr & exponent != nullptr){        
//         return factory.sign(sign).root(root->copy()).exponent(exponent->copy()).numerator(numerator->copy()).denominator(denominator->copy()).buildDivision().get(); 
//     }else if (root == nullptr & exponent != nullptr){
//         return factory.sign(sign).root(nullptr).exponent(exponent->copy()).numerator(numerator->copy()).denominator(denominator->copy()).buildSummation().get();
//     }else if (root != nullptr & exponent == nullptr){
//         return factory.sign(sign).root(root->copy()).exponent(nullptr).numerator(numerator->copy()).denominator(denominator->copy()).buildSummation().get();
//     }else{
//         return factory.sign(sign).root(nullptr).exponent(nullptr).numerator(numerator->copy()).denominator(denominator->copy()).buildSummation().get();
//     } 
// }

// string Division::toString(){
//     string expressionStr = "";
//     expressionStr = numerator->toString() + '/' + denominator->toString();
//     if (!sign){
//         expressionStr = "-{" + expressionStr + '}';
//     }else{
//         expressionStr = '{' + expressionStr + '}';
//     }
//     if (root != nullptr){
//         if (!root->isOne()){
//             expressionStr = '[' + root->toString() + '|' + expressionStr + ']';
//         }
//     }
//     if (exponent != nullptr){
//         if (!exponent->isOne()){
//             expressionStr = expressionStr + exponent->exponentToString();
//         }
//     }
//     return expressionStr;
// }

// string Division::exponentToString(){
//     string expressionStr = this->toString();
//     if (sign){
//         return "^(" + expressionStr + ')';
//     }else{
//         return '^' + expressionStr;
//     }
// }
// #include "equationComponents.h"
// #include <algorithm>

// TermBase::TermBase(): 
//                 sign(true), 
//                 root(nullptr), 
//                 exponent(nullptr),
//                 parentExpression(nullptr){}

// TermBase::TermBase(bool sign, TermBase* root, TermBase* exponent): 
//                 sign(sign), 
//                 root(root), 
//                 exponent(exponent), 
//                 parentExpression(nullptr){}

// bool TermBase::getSign(){
//     return sign;
// }

// TermBase* TermBase::getRoot(){
//     return root;
// }

// TermBase* TermBase::getExponent(){
//     return exponent;
// }

// TermBase* TermBase::getParentExpression(){
//     return parentExpression;
// }

// std::string TermBase::getExpressionString(){
//     return expressionString;
// }

// void TermBase::setSign(bool s){
//     sign = s; 
//     updateExpressionString();
// }

// void TermBase::setRoot(TermBase* r){
//     root = r; 
//     parentExpression = r;
//     updateExpressionString();
// }

// void TermBase::setExponent(TermBase* e){
//     exponent = e; 
//     updateExpressionString();
// }

// void TermBase::setParentExpression(TermBase* p){
//     parentExpression = p;
    
// }

// void TermBase::updateExpressionString(){
//     if (parentExpression){
//         parentExpression->updateExpressionString();
//     }
//     expressionString = this->toString();
// }

// // bool TermBase::isEqual(TermBase* other){
// //     if (expressionString == other->getExpressionString()){
// //         return true;
// //     }else{
// //         return false;
// //     }
// // }

// void TermBase::getAllSubTerms(std::vector<TermBase*>& terms,
//                                 std::vector<TermBase*>& subTerms,
//                                 int start,
//                                 int end){
//     if (end == terms.size()){
//         return;
//     }else if (start > end){
//         getAllSubTerms(terms, subTerms, 0, end + 1);
//     }else{
//         if (end - start == 1){
//             subTerms.push_back(terms[start]);
//         }else{
//             std::vector<TermBase*> newSubTerms;
//             for (int i = start; i < end; i ++){
//                 newSubTerms.push_back(terms[i]);
//             }
//             if (newSubTerms.size() != 0){
//                 subTerms.push_back(new TermContainer(true, nullptr, nullptr, OperationType::Multiplication, newSubTerms));
//             }
            
//         }
        
//         getAllSubTerms(terms, subTerms, start + 1, end);
//     }   
//     return;

// }

#include "expression.h"
#include "expressionFactory.h"

Expression::Expression(): 
                    sign(true), 
                    root(nullptr), 
                    exponent(nullptr), 
                    parentExpression(nullptr){}

Expression::Expression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent): 
                    sign(sign), 
                    root(move(root)), 
                    exponent(move(exponent)), 
                    parentExpression(nullptr){}

bool Expression::getSign(){
    return sign;
}

ExpressionPtr Expression::getRoot(){
    return move(root); // must be moved because it is not a local variable
}

ExpressionPtr Expression::getExponent(){
    return move(exponent);
}

ExpressionPtr Expression::getParentExpression(){
    return move(parentExpression);
}

string Expression::getExpressionString(){
    return expressionString;
}

void Expression::setSign(bool s){
    sign = s;
}

void Expression::setRoot(ExpressionPtr& e){
    root = move(e);
}

void Expression::setExponent(ExpressionPtr& e){
    exponent = move(e);
}

void Expression::setParentExpression(ExpressionPtr& e){
    parentExpression = move(e);
}

void Expression::updateExpressionString(){
    if (parentExpression){
        parentExpression->updateExpressionString();
    }
    expressionString = this->toString();
}

void Expression::getAllSubTerms(vector<ExpressionPtr>& terms,
                                vector<ExpressionPtr>& subTerms,
                                int start,
                                int end){

    if (end == terms.size()){
        return;
    }else if (start > end){
        getAllSubTerms(terms, subTerms, 0, end + 1);
    }else{
        if (end - start == 1){
            subTerms.push_back(move(terms[start]));
        }else{
            vector<ExpressionPtr> newSubTerms;
            for (int i = start; i < end; i ++){
                newSubTerms.push_back(move(terms[i]));
            }
            if (newSubTerms.size() != 0){
                ExpressionFactory factory;
                ExpressionPtr subTerm = factory.operands(newSubTerms).buildMultiplication().get();
                subTerms.push_back(move(subTerm));
            }
            
        }
        
        getAllSubTerms(terms, subTerms, start + 1, end);
    }   
    return;

}

#include "expression.h"

Expression::Expression(): 
                    sign(true), 
                    root(nullptr), 
                    exponent(nullptr), 
                    parentExpression(nullptr){}

Expression::Expression(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent): 
                    sign(sign), 
                    root(move(root)), 
                    exponent(move(exponent)), 
                    parentExpression(nullptr){}

bool Expression::getSign(){
    return sign;
}

unique_ptr<Expression> Expression::getRoot(){
    return move(root);
}

unique_ptr<Expression> Expression::getExponent(){
    return move(exponent);
}

unique_ptr<Expression> Expression::getParentExpression(){
    return move(parentExpression);
}

string Expression::getExpressionString(){
    return expressionString;
}

void Expression::setSign(bool s){
    sign = s;
}

void Expression::setRoot(unique_ptr<Expression>& e){
    root = move(e);
}

void Expression::setExponent(unique_ptr<Expression>& e){
    exponent = move(e);
}

void Expression::setParentExpression(unique_ptr<Expression>& e){
    parentExpression = move(e);
}

void Expression::updateExpressionString(){
    if (parentExpression){
        parentExpression->updateExpressionString();
    }
    expressionString = this->toString();
}

void Expression::getAllSubTerms(vector<unique_ptr<Expression>>& terms,
                                vector<unique_ptr<Expression>>& subTerms,
                                int start,
                                int end){
    //int toPush = 3;
    //ints.push_back(toPush);

    if (end == terms.size()){
        return;
    }else if (start > end){
        getAllSubTerms(terms, subTerms, 0, end + 1);
    }else{
        if (end - start == 1){
            subTerms.push_back(move(terms[start]));
        }else{
            vector<unique_ptr<Expression>> newSubTerms;
            for (int i = start; i < end; i ++){
                newSubTerms.push_back(move(terms[i]));
            }
            if (newSubTerms.size() != 0){
                subTerms.push_back(move(make_unique<Multiplication>(true, nullptr, nullptr, newSubTerms)));
            }
            
        }
        
        getAllSubTerms(terms, subTerms, start + 1, end);
    }   
    return;

}

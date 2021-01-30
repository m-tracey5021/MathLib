#include "expression.h"

Expression::Expression(): 
                    sign(true), 
                    root(nullptr), 
                    exponent(nullptr), 
                    parentExpression(nullptr){}

Expression::Expression(bool sign, unique_ptr<Expression> root, unique_ptr<Expression> exponent): 
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

void Expression::setSign(bool s){
    sign = s;
}

void Expression::setRoot(unique_ptr<Expression> e){
    root = move(e);
}

void Expression::setExponent(unique_ptr<Expression> e){
    exponent = move(e);
}

void Expression::setParentExpression(unique_ptr<Expression> e){
    parentExpression = move(e);
}

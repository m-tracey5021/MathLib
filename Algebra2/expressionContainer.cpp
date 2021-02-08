#include "expression.h"

ExpressionContainer::ExpressionContainer(): expression(nullptr){} // Default constructor

ExpressionContainer::ExpressionContainer(Expression& e): expression(&e){} // Custom constructor

ExpressionContainer::ExpressionContainer(const ExpressionContainer& ec): expression(deepCopy()){} // Copy (calls copy constructor of subclass)

ExpressionContainer::ExpressionContainer(ExpressionContainer&& ec){ // Move
    expression = ec.expression;
    ec.expression = nullptr;
}

ExpressionContainer& ExpressionContainer::operator= (const ExpressionContainer& ec){ // Assignment overload
    if (this != &ec){
        Expression* tmp = ec.expression;
        delete expression;
        expression = tmp;
    }else{
        return *this;
    }
}

// ExpressionContainer::~ExpressionContainer(){ // Destructor
//     delete expression;
// }


bool ExpressionContainer::isEmpty(){
    if (expression){
        return false;
    }else{
        return true;
    }
}

ExpressionContainer ExpressionContainer::copyContainer(bool deep = true){
    Expression* toPass;
    if (deep){
        toPass = deepCopy();
    }else{
        toPass = shallowCopy();
    }
    return ExpressionContainer(*toPass);
}

Expression* ExpressionContainer::deepCopy(){
    if (expression){
        return expression->copyExpression().expression;
    }else{
        return nullptr;
    }
    
}

Expression* ExpressionContainer::shallowCopy(){
    Expression* copy(expression);
    return copy;
}

vector<ExpressionContainer> ExpressionContainer::getContent(){
    return expression->getContent();
}
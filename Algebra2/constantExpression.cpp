#include "expression.h"

ConstantExpression::ConstantExpression(): Expression(){}

ConstantExpression::ConstantExpression(bool sign, unique_ptr<Expression> root, unique_ptr<Expression> exponent, int ConstantExpression): Expression(sign, move(root), move(exponent)), constant(constant){}

ConstantExpression::~ConstantExpression(){
    root.reset();
    exponent.reset();
    parentExpression.reset();
    delete &root;
    delete &exponent;
    delete &parentExpression;
}

int ConstantExpression::getConstant(){
    return constant;
}

void ConstantExpression::setConstant(int c){
    constant = c;
}

int* ConstantExpression::getValue(){
    return &constant;
}

vector<unique_ptr<Expression>> ConstantExpression::getContent(){
    unique_ptr<ConstantExpression> ptr (this);
    vector<unique_ptr<Expression>> content;
    content.push_back(move(ptr));
    return content;
}

void ConstantExpression::appendExpression(Expression& e){}

void ConstantExpression::removeExpression(int i){}

void ConstantExpression::replaceExpression(int i, Expression& e){}

void ConstantExpression::sanitise(){}

bool ConstantExpression::isEqual(Expression& other){return other.isEqual(*this);}

bool ConstantExpression::isEqual(Summation& other){return false;}

bool ConstantExpression::isEqual(Multiplication& other){return false;}

bool ConstantExpression::isEqual(Division& other){return false;}

bool ConstantExpression::isEqual(ConstantExpression& other){
    if (other.getConstant() == constant){
        return true;
    }else{
        return false;
    }
}

bool ConstantExpression::isEqual(VariableExpression& other){return false;}

bool ConstantExpression::isOne(){
    if (constant == 1){
        return true;
    }else{
        return false;
    }
}

bool ConstantExpression::isAtomic(){
    return true;
}

bool ConstantExpression::isAtomicExponent(){
    if (constant == 1){
        return true;
    }else{
        return false;;
    }
}

bool ConstantExpression::isAtomicNumerator(){
    if (constant == 1){
        return true;
    }else{
        return false;;
    }
}

bool ConstantExpression::isLikeExpression(Expression& other){
    return false;
}

bool ConstantExpression::isMergeable(){
    return true;
}

unique_ptr<Expression> ConstantExpression::sum(Summation s){
    unique_ptr<Expression> ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
    return ConstantExpressionPtr;
}

unique_ptr<Expression> ConstantExpression::sum(Multiplication m){
    unique_ptr<Expression> ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
    return ConstantExpressionPtr;
}

unique_ptr<Expression> ConstantExpression::sum(Division d){
    unique_ptr<Expression> ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
    return ConstantExpressionPtr;
}

unique_ptr<Expression> ConstantExpression::sum(ConstantExpression c){
    unique_ptr<Expression> ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
    return ConstantExpressionPtr;
}

unique_ptr<Expression> ConstantExpression::sum(VariableExpression v){
    unique_ptr<Expression> ConstantExpressionPtr (new ConstantExpression(true, nullptr, nullptr, 1));
    return ConstantExpressionPtr;
}

unique_ptr<Expression> ConstantExpression::expandForExponent(){
    if (!exponent){
        return unique_ptr<Expression> (this);
    }else{
        unique_ptr<Expression> expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

unique_ptr<Expression> ConstantExpression::expandAsExponent(Expression& baseExpression){
    unique_ptr<Expression> expandedTerm (new Multiplication());

    if (!sign){
        expandedTerm = expandAsNegativeExponent(baseExpression);
        return expandedTerm;
    }else{
        if (constant > 1){
            for (int i = 0; i < constant; i ++){
                unique_ptr<Expression> copiedBase (baseExpression.copy());
                copiedBase->setExponent(nullptr);
                expandedTerm->appendExpression(*copiedBase);
            }
            return expandedTerm;
        }else{
            return unique_ptr<Expression> (this);
        }
    }
}

unique_ptr<Expression> ConstantExpression::expandAsConstNum(Expression& baseExpression, Division& baseDivision){

    unique_ptr<Expression> expandedTerm (new Multiplication());
    unique_ptr<Expression> numerator (new ConstantExpression(true, nullptr, nullptr, 1));
    unique_ptr<Expression> denominator (baseDivision.getContent()[1]->copy());

    unique_ptr<Expression> newExponent (new Division(true, nullptr, nullptr, move(numerator), move(denominator)));
    unique_ptr<Expression> newTerm (baseExpression.copy());
    newTerm->setExponent(move(newExponent));


    for (int i = 0; i < constant; i ++){
        expandedTerm->appendExpression(*newTerm);
    }

    return expandedTerm;
}

unique_ptr<Expression> ConstantExpression::expandAsNegativeExponent(Expression& baseExpression){
    unique_ptr<Expression> expandedTerm (new Multiplication());

    for (int i = 0; i < constant; i ++){
        
        unique_ptr<Expression> newDenom (baseExpression.copy());
        newDenom->setExponent(nullptr);
        
        unique_ptr<Expression> newRational (new Division(true, 
                                                         nullptr, 
                                                         nullptr, 
                                                         unique_ptr<Expression> (new ConstantExpression(true, nullptr, nullptr, 1)), 
                                                         move(newDenom)));

        expandedTerm->appendExpression(*newRational);
    }
    return expandedTerm;
}

unique_ptr<Expression> ConstantExpression::factor(){
    return unique_ptr<Expression> (this);
}

vector<unique_ptr<Expression>> ConstantExpression::getConstantFactors(){
    vector<unique_ptr<Expression>> ConstantExpressionFactors;
    for (int i = 1; i <= constant; i ++){
        if (constant % i == 0){
            ConstantExpressionFactors.push_back(unique_ptr<Expression> (new ConstantExpression(true, nullptr, nullptr, i)));
        }
    }
    return ConstantExpressionFactors;
}

vector<unique_ptr<Expression>> ConstantExpression::getAllFactors(){

    vector<unique_ptr<Expression>> factors;
    vector<unique_ptr<Expression>> ConstantExpressionFactors = getConstantFactors();

    unique_ptr<Expression> expanded = expandForExponent();
    vector<unique_ptr<Expression>> expandedTerms = expanded->getContent();
    getAllSubTerms(expandedTerms, factors, 0, 0);

    for (unique_ptr<Expression>& cf : ConstantExpressionFactors){
        factors.push_back(move(cf));
    }
    return factors;
}

Expression* ConstantExpression::copy(){
    if (root != nullptr & exponent != nullptr){
        return new ConstantExpression(sign, unique_ptr<Expression> (root->copy()), unique_ptr<Expression> (exponent->copy()), constant);
    }else if (root == nullptr & exponent != nullptr){
        return new ConstantExpression(sign, nullptr, unique_ptr<Expression> (exponent->copy()), constant);
    }else if (root != nullptr & exponent == nullptr){
        return new ConstantExpression(sign, unique_ptr<Expression> (root->copy()), nullptr, constant);
    }else{
        return new ConstantExpression(sign, nullptr, nullptr, constant);
    }
    
}

string ConstantExpression::toString(){
    string expressionString = "";
    if (!sign){
        expressionString += '-';
    }

    expressionString += std::to_string(constant);

    if (root != nullptr){
        if (!root->isOne()){
            expressionString = '[' + root->toString() + '|' + expressionString + ']';
        }
    }
    if (exponent != nullptr){
        if (!exponent->isOne()){
            expressionString = expressionString + exponent->exponentToString();
        }
    }
    return expressionString;
}

string ConstantExpression::exponentToString(){
    return "^(" + this->toString() + ')';
}
#include "expression.h"

VariableExpression::VariableExpression(): Expression(){}

VariableExpression::VariableExpression(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent, char VariableExpression): Expression(sign, root, exponent), variable(variable){
    updateExpressionString();
}

VariableExpression::~VariableExpression(){
    root.reset();
    exponent.reset();
    parentExpression.reset();
    delete &root;
    delete &exponent;
    delete &parentExpression;
}

char VariableExpression::getVariable(){
    return variable;
}

void VariableExpression::setVariable(char v){
    variable = v;
}

int* VariableExpression::getValue(){
    return nullptr;
}

vector<unique_ptr<Expression>> VariableExpression::getContent(){
    unique_ptr<VariableExpression> ptr (this);
    vector<unique_ptr<Expression>> content;
    content.push_back(move(ptr));
    return content;
}

void VariableExpression::appendExpression(Expression& e){}

void VariableExpression::removeExpression(int i){}

void VariableExpression::replaceExpression(int i, Expression& e){}

void VariableExpression::sanitise(){
    
}

bool VariableExpression::isEqual(Expression& other){return other.isEqual(*this);}

bool VariableExpression::isEqual(Summation& other){return false;}

bool VariableExpression::isEqual(Multiplication& other){return false;}

bool VariableExpression::isEqual(Division& other){return false;}

bool VariableExpression::isEqual(ConstantExpression& other){return false;}

bool VariableExpression::isEqual(VariableExpression& other){
    if (variable == other.getVariable()){
        return true;
    }else{
        return false;
    }
}

bool VariableExpression::isOne(){return false;}

bool VariableExpression::isAtomic(){return true;}

bool VariableExpression::isAtomicExponent(){return true;}

bool VariableExpression::isAtomicNumerator(){return true;}

bool VariableExpression::isLikeExpression(Expression& other){
    return false;
}

bool VariableExpression::isMergeable(){
    return true;
}

unique_ptr<Expression> VariableExpression::mergeMultiplications(Expression& other){
    if (other.isMergeable()){

        vector<unique_ptr<Expression>> tmpTerms;
        tmpTerms.push_back(move(unique_ptr<Expression> (this)));

        vector<unique_ptr<Expression>> otherTerms = other.getContent();
        for (int j = 0; j < otherTerms.size(); j ++){
            tmpTerms.push_back(move(otherTerms[j]));
        }
        unique_ptr<Expression> ();
        unique_ptr<Expression> null2 ();
        return unique_ptr<Expression> (new Multiplication(true, unique_ptr<Expression>(), unique_ptr<Expression>(), tmpTerms));
    }else{
        return nullptr;
    }
}

unique_ptr<Expression> VariableExpression::expandForExponent(){
    if (!exponent){
        return unique_ptr<Expression> (this);
    }else{
        unique_ptr<Expression> expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

unique_ptr<Expression> VariableExpression::expandAsExponent(Expression& baseExpression){
    return unique_ptr<Expression> (&baseExpression);
}

unique_ptr<Expression> VariableExpression::expandAsConstNum(Expression& baseExpression, Division& baseDivision){
    return unique_ptr<Expression> (&baseExpression);
}

unique_ptr<Expression> VariableExpression::expandAsNegativeExponent(Expression& baseExpression){
    return unique_ptr<Expression> (&baseExpression);
}

unique_ptr<Expression> VariableExpression::factor(){
    return nullptr;
}

std::vector<unique_ptr<Expression>> VariableExpression::getConstantFactors(){
    std::vector<unique_ptr<Expression>> constantFactors;
    return constantFactors;
}

std::vector<unique_ptr<Expression>> VariableExpression::getAllFactors(){

    std::vector<unique_ptr<Expression>> factors;
    std::vector<unique_ptr<Expression>> expandedTerms = expandForExponent()->getContent();
    getAllSubTerms(expandedTerms, factors, 0, 0);

    return factors;

}

unique_ptr<Expression> VariableExpression::copy(){

    if (root != nullptr & exponent != nullptr){
        return make_unique<VariableExpression>(sign, root->copy(), exponent->copy(), variable);
    }else if (root == nullptr & exponent != nullptr){
        return make_unique<VariableExpression>(sign, nullptr, exponent->copy(), variable);
    }else if (root != nullptr & exponent == nullptr){
        return make_unique<VariableExpression>(sign, root->copy(), nullptr, variable);
    }else{
        return make_unique<VariableExpression>(sign, nullptr, nullptr, variable);
    }
}

std::string VariableExpression::toString(){
    std::string termStr = "";
    if (!sign){
        termStr += '-';
    }

    termStr += variable;

    if (root != nullptr){
        if (!root->isOne()){
            termStr = '[' + root->toString() + '|' + termStr + ']';
        }
    }
    if (exponent != nullptr){
        if (!exponent->isOne()){
            termStr = termStr + exponent->exponentToString();
            
        }
    }

    return termStr;
}

std::string VariableExpression::exponentToString(){
    return "^(" + this->toString() + ')';
}
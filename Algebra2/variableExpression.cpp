#include "expression.h"
#include "expressionFactory.h"

VariableExpression::VariableExpression(): Expression(){}

VariableExpression::VariableExpression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, char variable): Expression(sign, root, exponent), variable(variable){}

// VariableExpression::~VariableExpression(){
//     root.reset();
//     exponent.reset();
//     parentExpression.reset();
//     delete &root;
//     delete &exponent;
//     delete &parentExpression;
// }

char VariableExpression::getVariable(){
    return variable;
}

void VariableExpression::setVariable(char v){
    variable = v;
}

IntPtr VariableExpression::getValue(){
    IntPtr empty = IntPtr();
    return empty;
}

vector<ExpressionPtr> VariableExpression::getContent(){
    ExpressionPtr thisPtr  = VEPtr(this);
    vector<ExpressionPtr> content;
    content.push_back(move(thisPtr));
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

ExpressionPtr VariableExpression::sum(Summation& s){
    return nullptr;
}

ExpressionPtr VariableExpression::sum(Multiplication& m){
    return nullptr;
}

ExpressionPtr VariableExpression::sum(Division& d){
    return nullptr;
}

ExpressionPtr VariableExpression::sum(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr VariableExpression::sum(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr VariableExpression::multiply(Summation& m){
    return nullptr;
}

ExpressionPtr VariableExpression::multiply(Multiplication& m){
    return nullptr;
}

ExpressionPtr VariableExpression::multiply(Division& d){
    return nullptr;
}

ExpressionPtr VariableExpression::multiply(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr VariableExpression::multiply(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr VariableExpression::divide(Summation& m){
    return nullptr;
}

ExpressionPtr VariableExpression::divide(Multiplication& m){
    return nullptr;
}

ExpressionPtr VariableExpression::divide(Division& d){
    return nullptr;
}

ExpressionPtr VariableExpression::divide(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr VariableExpression::divide(VariableExpression& ve){
    return nullptr;
}


ExpressionPtr VariableExpression::mergeMultiplications(Expression& other){
    ExpressionFactory factory;
    if (other.isMergeable()){

        vector<ExpressionPtr> tmpTerms;
        tmpTerms.push_back(move(ExpressionPtr (this)));

        vector<ExpressionPtr> otherTerms = other.getContent();
        for (int j = 0; j < otherTerms.size(); j ++){
            tmpTerms.push_back(move(otherTerms[j]));
        }
        return factory.sign(true).root(nullptr).exponent(nullptr).operands(tmpTerms).buildMultiplication().get();
    }else{
        return factory.buildMultiplication().get();
    }
}

ExpressionPtr VariableExpression::expandForExponent(){
    if (!exponent){
        return ExpressionPtr (this);
    }else{
        ExpressionPtr expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

ExpressionPtr VariableExpression::expandAsExponent(Expression& baseExpression){
    return ExpressionPtr (&baseExpression);
}

ExpressionPtr VariableExpression::expandAsConstNum(Expression& baseExpression, Expression& baseDivision){
    return ExpressionPtr (&baseExpression);
}

ExpressionPtr VariableExpression::expandAsNegativeExponent(Expression& baseExpression){
    return ExpressionPtr (&baseExpression);
}

ExpressionPtr VariableExpression::factor(){
    return nullptr;
}

std::vector<ExpressionPtr> VariableExpression::getConstantFactors(){
    std::vector<ExpressionPtr> constantFactors;
    return constantFactors;
}

std::vector<ExpressionPtr> VariableExpression::getAllFactors(){

    std::vector<ExpressionPtr> factors;
    std::vector<ExpressionPtr> expandedTerms = expandForExponent()->getContent();
    getAllSubTerms(expandedTerms, factors, 0, 0);

    return factors;

}

ExpressionPtr VariableExpression::copy(){
    ExpressionFactory factory;
    if (root != nullptr & exponent != nullptr){        
        return factory.sign(sign).root(root->copy()).exponent(exponent->copy()).variable(variable).buildVariableExpression().get(); 
    }else if (root == nullptr & exponent != nullptr){
        return factory.sign(sign).root(nullptr).exponent(exponent->copy()).variable(variable).buildVariableExpression().get();
    }else if (root != nullptr & exponent == nullptr){
        return factory.sign(sign).root(root->copy()).exponent(nullptr).variable(variable).buildVariableExpression().get();
    }else{
        return factory.sign(sign).root(nullptr).exponent(nullptr).variable(variable).buildVariableExpression().get();
    } 
}

std::string VariableExpression::toString(){
    std::string expressionStr = "";
    if (!sign){
        expressionStr += '-';
    }

    expressionStr += variable;

    if (root != nullptr){
        if (!root->isOne()){
            expressionStr = '[' + root->toString() + '|' + expressionStr + ']';
        }
    }
    if (exponent != nullptr){
        if (!exponent->isOne()){
            expressionStr = expressionStr + exponent->exponentToString();
            
        }
    }

    return expressionStr;
}

std::string VariableExpression::exponentToString(){
    return "^(" + this->toString() + ')';
}
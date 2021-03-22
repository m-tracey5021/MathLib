#include "expression.h"
#include "expressionFactory.h"

Summation::Summation(): Expression(){}

Summation::Summation(bool sign, 
                        ExpressionPtr& root, 
                        ExpressionPtr& exponent, 
                        vector<ExpressionPtr>& operands): 
                        Expression(sign, root, exponent), operands(move(operands)){}

// Summation::~Summation(){
//     root.reset();
//     exponent.reset();
//     parentExpression.reset();
//     delete &root;
//     delete &exponent;
//     delete &parentExpression;
//     operands.clear();
//     delete &operands;
// }

vector<ExpressionPtr> Summation::getOperands(){
    return move(operands);
}

void Summation::setOperands(vector<ExpressionPtr>& o){
    operands = move(o);
}

IntPtr Summation::getValue(){
    IntPtr empty = IntPtr();
    return empty;
}

vector<ExpressionPtr> Summation::getContent(){
    return move(operands);
}

void Summation::appendExpression(Expression& e){
    ExpressionPtr toAppend = ExpressionPtr(&e);
    ExpressionPtr thisPtr = ExpressionPtr(this);
    operands.push_back(move(toAppend));
    e.setParentExpression(thisPtr);
    updateExpressionString();
}

void Summation::removeExpression(int i){operands.erase(operands.begin() + i); updateExpressionString();}

void Summation::replaceExpression(int i, Expression& e){
    ExpressionPtr toReplace = ExpressionPtr(&e);
    operands.insert(operands.begin() + i, move(toReplace));
    removeExpression(i + 1);
}

void Summation::sanitise(){}

bool Summation::isEqual(Expression& other){return other.isEqual(*this);}

bool Summation::isEqual(Summation& other){
    vector<ExpressionPtr> otherOperands = other.getOperands();
    if (operands.size() == otherOperands.size()){
        for (int i = 0; i < operands.size(); i ++){
            if (!operands[i]->isEqual(*otherOperands[i])){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }   
}

bool Summation::isEqual(Multiplication& other){return false;}

bool Summation::isEqual(Division& other){return false;}

bool Summation::isEqual(ConstantExpression& other){return false;}

bool Summation::isEqual(VariableExpression& other){return false;}

bool Summation::isOne(){return false;}

bool Summation::isAtomic(){return false;}

bool Summation::isAtomicExponent(){return false;}

bool Summation::isAtomicNumerator(){return false;}

bool Summation::isLikeExpression(Expression& e){return false;}

bool Summation::isMergeable(){return false;}

ExpressionPtr Summation::sum(Summation& s){
    return nullptr;
}

ExpressionPtr Summation::sum(Multiplication& m){
    return nullptr;
}

ExpressionPtr Summation::sum(Division& d){
    return nullptr;
}

ExpressionPtr Summation::sum(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr Summation::sum(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr Summation::multiply(Summation& m){
    return nullptr;
}

ExpressionPtr Summation::multiply(Multiplication& m){
    return nullptr;
}

ExpressionPtr Summation::multiply(Division& d){
    return nullptr;
}

ExpressionPtr Summation::multiply(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr Summation::multiply(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr Summation::divide(Summation& m){
    return nullptr;
}

ExpressionPtr Summation::divide(Multiplication& m){
    return nullptr;
}

ExpressionPtr Summation::divide(Division& d){
    return nullptr;
}

ExpressionPtr Summation::divide(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr Summation::divide(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr Summation::mergeMultiplications(Expression& other){
    return ExpressionPtr(&other);
}

ExpressionPtr Summation::expandForExponent(){
    if (!exponent){
        return ExpressionPtr(this);
    }else{
        ExpressionPtr expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

ExpressionPtr Summation::expandAsExponent(Expression& baseExpression){

    ExpressionPtr expanded = make_unique<Multiplication>();

    // expand the exponents of the innerTerms

    ExpressionPtr copied = this->copy();
    vector<ExpressionPtr> copiedContent = copied->getContent();

    for (int i = 0; i < copiedContent.size(); i ++){
        ExpressionPtr innerTerm = move(copiedContent[i]);
        ExpressionPtr innerExponent = innerTerm->getExponent();
        if (innerExponent != nullptr){
            if (!innerExponent->isAtomicExponent()){
                ExpressionPtr expandedInnerTerm = innerTerm->expandForExponent();
                copied->replaceExpression(i, *expandedInnerTerm);
            }
        }
    }
    
    // expand the exponent of the main exponent

    if (copied->getExponent() != nullptr){  
        copied = move(copied->expandForExponent());
    }
    copiedContent = copied->getContent();

    // expand the main exponent over the baseTerm passed in

    if (!sign){
        expanded = move(expandAsNegativeExponent(baseExpression));
    }else{
        if (isAtomicExponent()){
            return ExpressionPtr(&baseExpression);
        }else if (isAtomic() & !isAtomicExponent()){
            expanded = move(expandAsExponent(baseExpression));
        }else{
            
            for (int i = 0; i < copiedContent.size(); i ++){

                ExpressionPtr newExpression = baseExpression.copy();
                ExpressionPtr newExponent = move(copiedContent[i]->copy());
                newExpression->setExponent(newExponent);
                expanded->appendExpression(*newExpression);
            }
        }
    }
    

    /* 
        check that the resultant expandedTerm is fully expanded, i.e. all
        of the exponents are in atomic form, either 1 or n or nm or 1/n 
    */

    if (expanded->getContent().size() == 0){
        return ExpressionPtr(this);
    }else{
        for (int i = 0; i < expanded->getContent().size(); i ++){
            ExpressionPtr ithExpandedTerm = move(expanded->getContent()[i]);
            ExpressionPtr toReplace = ithExpandedTerm->expandForExponent();
            expanded->replaceExpression(i, *toReplace); // this is very inefficient
        }
        return expanded;
    }
}

ExpressionPtr Summation::expandAsConstNum(Expression& baseExpression, Expression& baseDivision){
    return ExpressionPtr(&baseExpression);
}

ExpressionPtr Summation::expandAsNegativeExponent(Expression& baseExpression){
    return ExpressionPtr(&baseExpression);
}

ExpressionPtr Summation::factor(){
    return nullptr;
}

vector<ExpressionPtr> Summation::getConstantFactors(){
    vector<ExpressionPtr> constantFactors;
    for (int i = 0; i < operands.size(); i ++){
        ExpressionPtr ithExpression = move(operands[i]);
        vector<ExpressionPtr> ithConstantFactors = ithExpression->getConstantFactors();
        for(int j = 0; j < ithConstantFactors.size(); j ++){
            constantFactors.push_back(move(ithConstantFactors[j]));
        }
        //constantFactors.insert(constantFactors.end(), ithConstantFactors.begin(), ithConstantFactors.end());
    }
    
    return constantFactors;
}

vector<ExpressionPtr> Summation::getAllFactors(){
    vector<ExpressionPtr> dummy;
    return dummy;
}

ExpressionPtr Summation::copy(){
    ExpressionFactory factory;
    vector<ExpressionPtr> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        ExpressionPtr ithCopy = move(operands[i]->copy());
        copiedContent.push_back(move(ithCopy));
    }
    if (root != nullptr & exponent != nullptr){        
        return factory.sign(sign).root(root->copy()).exponent(exponent->copy()).operands(copiedContent).buildSummation().get(); 
    }else if (root == nullptr & exponent != nullptr){
        return factory.sign(sign).root(nullptr).exponent(exponent->copy()).operands(copiedContent).buildSummation().get();
    }else if (root != nullptr & exponent == nullptr){
        return factory.sign(sign).root(root->copy()).exponent(nullptr).operands(copiedContent).buildSummation().get();
    }else{
        return factory.sign(sign).root(nullptr).exponent(nullptr).operands(copiedContent).buildSummation().get();
    } 
}

string Summation::toString(){
    string expressionStr = "";
    for (int i = 0; i < operands.size(); i ++){
        if (i == 0){
            expressionStr += operands[i]->toString();
        }else{
            if (operands[i]->getSign()){
                expressionStr += '+' + operands[i]->toString();
            }else{
                expressionStr += operands[i]->toString();
            }
        }
    }
    if (!sign){
        expressionStr = "-(" + expressionStr + ')';
    }else{
        if ((operands.size() != 1 & parentExpression != nullptr) | exponent != nullptr){
            expressionStr = '(' + expressionStr + ')';
        }
    }
    return expressionStr;
}

string Summation::exponentToString(){
    string expressionStr = this->toString();
    if (sign){
        return "^(" + expressionStr + ')';
    }else{
        return '^' + expressionStr;
    }
}
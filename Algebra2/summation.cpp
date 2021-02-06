#include "expression.h"

Summation::Summation(): Expression(){}

Summation::Summation(bool sign, 
                        ExpressionContainer& root, 
                        ExpressionContainer& exponent, 
                        vector<ExpressionContainer>& operands): 
                        Expression(sign, root, exponent), operands(operands){}

Summation::~Summation(){
    operands.clear();
    delete &operands;
}

vector<unique_ptr<Expression>> Summation::getOperands(){
    return operands;
}

void Summation::setOperands(vector<unique_ptr<Expression>> o){
    operands = o;
}

int* Summation::getValue(){
    return nullptr;
}

vector<unique_ptr<Expression>> Summation::getContent(){
    return operands;
}

void Summation::appendExpression(Expression& e){
    operands.push_back(move(unique_ptr<Expression> (&e)));
    unique_ptr<Expression> thisPtr (this);
    e.setParentExpression(thisPtr);
    updateExpressionString();
}

void Summation::removeExpression(int i){operands.erase(operands.begin() + i); updateExpressionString();}

void Summation::replaceExpression(int i, Expression& e){operands.insert(operands.begin() + i, unique_ptr<Expression> (&e)); removeExpression(i + 1);}

void Summation::sanitise(){}

bool Summation::isEqual(Expression& other){return other.isEqual(*this);}

bool Summation::isEqual(Summation& other){
    vector<unique_ptr<Expression>> otherOperands = other.getOperands();
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

unique_ptr<Expression> Summation::mergeMultiplications(Expression& other){return nullptr;}

unique_ptr<Expression> Summation::expandForExponent(){
    if (!exponent){
        return unique_ptr<Expression> (this);
    }else{
        unique_ptr<Expression> expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

unique_ptr<Expression> Summation::expandAsExponent(Expression& baseExpression){

    unique_ptr<Expression> expanded = make_unique<Multiplication>();

    // expand the exponents of the innerTerms

    unique_ptr<Expression> copied = this->copy();
    vector<unique_ptr<Expression>> copiedContent = copied->getContent();

    for (int i = 0; i < copiedContent.size(); i ++){
        unique_ptr<Expression> innerTerm = move(copiedContent[i]);
        unique_ptr<Expression> innerExponent = innerTerm->getExponent();
        if (innerExponent != nullptr){
            if (!innerExponent->isAtomicExponent()){
                unique_ptr<Expression> expandedInnerTerm = innerTerm->expandForExponent();
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
            return unique_ptr<Expression>(&baseExpression);
        }else if (isAtomic() & !isAtomicExponent()){
            expanded = move(expandAsExponent(baseExpression));
        }else{
            
            for (int i = 0; i < copiedContent.size(); i ++){

                unique_ptr<Expression> newExpression = move(baseExpression.copy());
                unique_ptr<Expression> newExponent = move(copiedContent[i]->copy());
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
        return unique_ptr<Expression>(this);
    }else{
        for (int i = 0; i < expanded->getContent().size(); i ++){
            unique_ptr<Expression> ithExpandedTerm = move(expanded->getContent()[i]);
            expanded->replaceExpression(i, *ithExpandedTerm->expandForExponent()); // this is very inefficient
        }
        return expanded;
    }
}

unique_ptr<Expression> Summation::expandAsConstNum(Expression& baseExpression, Division& baseDivision){
    return unique_ptr<Expression>(&baseExpression);
}

unique_ptr<Expression> Summation::expandAsNegativeExponent(Expression& baseExpression){
    return unique_ptr<Expression>(&baseExpression);
}

unique_ptr<Expression> Summation::factor(){
    return nullptr;
}

vector<unique_ptr<Expression>> Summation::getConstantFactors(){
    vector<unique_ptr<Expression>> constantFactors;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Expression> ithExpression = move(operands[i]);
        vector<unique_ptr<Expression>> ithConstantFactors = ithExpression->getConstantFactors();
        constantFactors.insert(constantFactors.end(), ithConstantFactors.begin(), ithConstantFactors.end());
    }
    
    return constantFactors;
}

vector<unique_ptr<Expression>> Summation::getAllFactors(){
    vector<unique_ptr<Expression>> dummy;
    return dummy;
}

unique_ptr<Expression> Summation::copy(){
    vector<unique_ptr<Expression>> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Expression> ithCopy = move(operands[i]->copy());
        copiedContent.push_back(move(ithCopy));
    }

    if (root != nullptr & exponent != nullptr){
        return make_unique<Summation>(sign, root->copy(), exponent->copy(), copiedContent);
    }else if (root == nullptr & exponent != nullptr){
        return make_unique<Summation>(sign, nullptr, exponent->copy(), copiedContent);
    }else if (root != nullptr & exponent == nullptr){
        return make_unique<Summation>(sign, root->copy(), nullptr, copiedContent);
    }else{
        return make_unique<Summation>(sign, nullptr, nullptr, copiedContent);
    } 
}
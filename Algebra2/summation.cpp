#include "expression.h"

Summation::Summation(): Expression(){}

Summation::Summation(bool sign, 
                        unique_ptr<Expression> root, 
                        unique_ptr<Expression> exponent, 
                        vector<unique_ptr<Expression>> operands): 
                        Expression(sign, move(root), move(exponent)), operands(operands){}

Summation::~Summation(){
    root.reset();
    exponent.reset();
    parentExpression.reset();
    delete &root;
    delete &exponent;
    delete &parentExpression;
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
    e.setParentExpression(unique_ptr<Expression> (this));
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

    unique_ptr<Expression> expanded = make_unique<Multiplication>(new Multiplication());

    // expand the exponents of the innerTerms

    unique_ptr<Summation> copied = make_unique<Summation>(static_cast<Summation*> (this->copy()));
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
        copied = make_unique<Summation>(static_cast<Summation*> (copied->expandForExponent().get()));
    }
    copiedContent = copied->getContent();

    // expand the main exponent over the baseTerm passed in

    if (!sign){
        expanded = make_unique<Expression>(expandAsNegativeExponent(baseExpression));
    }else{
        if (isAtomicExponent()){
            return make_unique<Expression>(&baseExpression);
        }else if (isAtomic() & !isAtomicExponent()){
            expanded = make_unique<Expression>(expandAsExponent(baseExpression));
        }else{
            
            for (int i = 0; i < copiedContent.size(); i ++){

                unique_ptr<Expression> newExpression = make_unique<Expression>(*baseExpression.copy());
                unique_ptr<Expression> newExponent = make_unique<Expression>(copiedContent[i]->copy());
                newExpression->setExponent(move(newExponent));
                expanded->appendExpression(*newExpression);
            }
        }
    }
    

    /* 
        check that the resultant expandedTerm is fully expanded, i.e. all
        of the exponents are in atomic form, either 1 or n or nm or 1/n 
    */

    if (expanded->getContent().size() == 0){
        return make_unique<Expression>(this);
    }else{
        for (int i = 0; i < expanded->getContent().size(); i ++){
            unique_ptr<Expression> ithExpandedTerm = make_unique<Expression>(expanded->getContent()[i]);
            expanded->replaceExpression(i, *ithExpandedTerm->expandForExponent()); // this is very inefficient
        }
        return expanded;
    }
}

unique_ptr<Expression> Summation::expandAsConstNum(Expression& baseExpression, Division& baseDivision){
    return make_unique<Expression>(baseExpression);
}

unique_ptr<Expression> Summation::expandAsNegativeExponent(Expression& baseExpression){
    return make_unique<Expression>(baseExpression);
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

Expression* Summation::copy(){
    vector<unique_ptr<Expression>> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Expression> ithCopy = make_unique<Expression>(operands[i]->copy());
        copiedContent.push_back(move(ithCopy));
    }

    if (root != nullptr & exponent != nullptr){
        return new Summation(sign, make_unique<Expression>(root->copy()), make_unique<Expression>(exponent->copy()), copiedContent);
    }else if (root == nullptr & exponent != nullptr){
        return new Summation(sign, nullptr, make_unique<Expression>(exponent->copy()), copiedContent);
    }else if (root != nullptr & exponent == nullptr){
        return new Summation(sign, make_unique<Expression>(root->copy()), nullptr, copiedContent);
    }else{
        return new Summation(sign, nullptr, nullptr, copiedContent);
    } 
}
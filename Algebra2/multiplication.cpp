#include "expression.h"

Multiplication::Multiplication(): Expression(){}

Multiplication::Multiplication(bool sign, 
                        unique_ptr<Expression> root, 
                        unique_ptr<Expression> exponent, 
                        vector<unique_ptr<Expression>> operands): 
                        Expression(sign, move(root), move(exponent)), operands(operands){}

Multiplication::~Multiplication(){
    root.reset();
    exponent.reset();
    parentExpression.reset();
    delete &root;
    delete &exponent;
    delete &parentExpression;
    operands.clear();
    delete &operands;
}

vector<unique_ptr<Expression>> Multiplication::getOperands(){
    return operands;
}

void Multiplication::setOperands(vector<unique_ptr<Expression>> o){
    operands = o;
}

int* Multiplication::getValue(){
    return nullptr;
}

vector<unique_ptr<Expression>> Multiplication::getContent(){
    return operands;
}

void Multiplication::appendExpression(Expression& e){
    operands.push_back(move(unique_ptr<Expression> (&e)));
    e.setParentExpression(unique_ptr<Expression> (this));
    updateExpressionString();
}

void Multiplication::removeExpression(int i){operands.erase(operands.begin() + i); updateExpressionString();}

void Multiplication::replaceExpression(int i, Expression& e){operands.insert(operands.begin() + i, unique_ptr<Expression> (&e)); removeExpression(i + 1);}

void Multiplication::sanitise(){
    // make one term out of several multiplicative terms
    vector<unique_ptr<Expression>> sanitised;
    unique_ptr<Expression> merged;
    for (int i = 1; i < operands.size(); i++){
        if (!merged){
            merged = operands[0]->mergeMultiplications(*operands[i]);
        }else{
            merged = merged->mergeMultiplications(*operands[i]);
        }
    }

    if (!merged){
        sanitised = operands;
    }else{
        sanitised = merged->getContent();
    }
    
    // update coefficient
    int totalCoeff = 0;
    for (int i = 0; i < sanitised.size(); i ++){
        unique_ptr<Expression> current = move(sanitised[i]);
        int* valPtr = current->getValue();
        if (valPtr != nullptr & current->getExponent() == nullptr){
            int val = *valPtr;
            if (!totalCoeff){
                totalCoeff += val;
            }else{
                totalCoeff *= val;
            }
            sanitised.erase(sanitised.begin() + i);
            i --;
        }
    }
    if (totalCoeff){
        unique_ptr<ConstantExpression> coeff = make_unique<ConstantExpression>(new ConstantExpression(true, nullptr, nullptr, totalCoeff));
        sanitised.insert(sanitised.begin(), move(coeff));
    }
    operands = sanitised;
}

bool Multiplication::isEqual(Expression& other){return other.isEqual(*this);}

bool Multiplication::isEqual(Summation& other){return false;}

bool Multiplication::isEqual(Multiplication& other){
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

bool Multiplication::isEqual(Division& other){return false;}

bool Multiplication::isEqual(ConstantExpression& other){return false;}

bool Multiplication::isEqual(VariableExpression& other){return false;}

bool Multiplication::isOne(){return false;}

bool Multiplication::isAtomic(){return false;}

bool Multiplication::isAtomicExponent(){return false;}

bool Multiplication::isAtomicNumerator(){return false;}

bool Multiplication::isLikeExpression(Expression& e){return false;}

bool Multiplication::isMergeable(){return false;}

unique_ptr<Expression> Multiplication::mergeMultiplications(Expression& other){return nullptr;}

unique_ptr<Expression> Multiplication::expandForExponent(){
    if (!exponent){
        return unique_ptr<Expression> (this);
    }else{
        unique_ptr<Expression> expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

unique_ptr<Expression> Multiplication::expandAsExponent(Expression& baseExpression){

    unique_ptr<Expression> expanded = make_unique<Multiplication>(new Multiplication());

    // expand the exponents of the innerTerms

    unique_ptr<Multiplication> copied = make_unique<Multiplication>(static_cast<Multiplication*> (this->copy()));
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
        copied = make_unique<Multiplication>(static_cast<Multiplication*> (copied->expandForExponent().get()));
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

unique_ptr<Expression> Multiplication::expandAsConstNum(Expression& baseExpression, Division& baseDivision){
    return make_unique<Expression>(baseExpression);
}

unique_ptr<Expression> Multiplication::expandAsNegativeExponent(Expression& baseExpression){
    return make_unique<Expression>(baseExpression);
}

unique_ptr<Expression> Multiplication::factor(){
    return nullptr;
}

vector<unique_ptr<Expression>> Multiplication::getConstantFactors(){
    vector<unique_ptr<Expression>> constantFactors;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Expression> ithExpression = move(operands[i]);
        vector<unique_ptr<Expression>> ithConstantFactors = ithExpression->getConstantFactors();
        constantFactors.insert(constantFactors.end(), ithConstantFactors.begin(), ithConstantFactors.end());
    }
    
    return constantFactors;
}

vector<unique_ptr<Expression>> Multiplication::getAllFactors(){
    vector<unique_ptr<Expression>> dummy;
    return dummy;
}

Expression* Multiplication::copy(){
    vector<unique_ptr<Expression>> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Expression> ithCopy = make_unique<Expression>(operands[i]->copy());
        copiedContent.push_back(move(ithCopy));
    }

    if (root != nullptr & exponent != nullptr){
        return new Multiplication(sign, make_unique<Expression>(root->copy()), make_unique<Expression>(exponent->copy()), copiedContent);
    }else if (root == nullptr & exponent != nullptr){
        return new Multiplication(sign, nullptr, make_unique<Expression>(exponent->copy()), copiedContent);
    }else if (root != nullptr & exponent == nullptr){
        return new Multiplication(sign, make_unique<Expression>(root->copy()), nullptr, copiedContent);
    }else{
        return new Multiplication(sign, nullptr, nullptr, copiedContent);
    } 
}
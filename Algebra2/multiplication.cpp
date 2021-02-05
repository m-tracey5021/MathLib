#include "expression.h"

Multiplication::Multiplication(): Expression(){}

Multiplication::Multiplication(bool sign, 
                        unique_ptr<Expression>& root, 
                        unique_ptr<Expression>& exponent, 
                        vector<unique_ptr<Expression>>& operands): 
                        Expression(sign, root, exponent), operands(operands){}

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
    unique_ptr<Expression> thisPtr (this);
    e.setParentExpression(thisPtr);
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
        unique_ptr<ConstantExpression> coeff = make_unique<ConstantExpression>(true, nullptr, nullptr, totalCoeff);
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

unique_ptr<Expression> Multiplication::mergeMultiplications(Expression& other){
    vector<unique_ptr<Expression>> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        copiedContent.push_back(move(operands[i]));
    }
    vector<unique_ptr<Expression>> otherOperands = other.getContent();
    for (int j = 0; j < otherOperands.size(); j ++){
        copiedContent.push_back(move(otherOperands[j]));
    }
    return make_unique<Multiplication>(true, nullptr, nullptr, copiedContent);
}

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

    sanitise();

    unique_ptr<Expression> expanded = make_unique<Multiplication>();

    // expand the exponents of the innerTerms

    unique_ptr<Expression> copied = this->copy(); // make_unique<Multiplication>(static_cast<Multiplication*> (this->copy()));
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
            return unique_ptr<Expression> (&baseExpression);
        }else if (isAtomic() & !isAtomicExponent()){
            expanded = move(expandAsExponent(baseExpression));
        }else{
            
            int* coeffPtr = operands[0]->getValue();

            if (coeffPtr){
                int coeff = *coeffPtr;
                unique_ptr<Expression> newTerm = move(baseExpression.copy());
                unique_ptr<Expression> newExponent = copied->copy(); // make_unique<Multiplication>(static_cast<Multiplication*> (copied->copy()));
                newExponent->removeExpression(0);
                if (newExponent->getContent().size() == 1){
                    unique_ptr<Expression> singleExponent = move(newExponent->getContent()[0]);
                    singleExponent->setParentExpression(nullptr);
                    newTerm->setExponent(move(singleExponent));
                }else{
                    newTerm->setExponent(move(newExponent));
                }
                
                for (int i = 0; i < coeff; i ++){
                    expanded->appendExpression(*newTerm->copy());
                }
            }
            delete coeffPtr;
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

unique_ptr<Expression> Multiplication::expandAsConstNum(Expression& baseExpression, Division& baseDivision){
    return unique_ptr<Expression>(&baseExpression);
}

unique_ptr<Expression> Multiplication::expandAsNegativeExponent(Expression& baseExpression){
    return unique_ptr<Expression>(&baseExpression);
}

unique_ptr<Expression> Multiplication::factor(){
    return nullptr;
}

vector<unique_ptr<Expression>> Multiplication::getConstantFactors(){
    vector<unique_ptr<Expression>> constantFactors = operands[0]->getConstantFactors();
    return constantFactors;
}

vector<unique_ptr<Expression>> Multiplication::getAllFactors(){
    vector<unique_ptr<Expression>> dummy;
    return dummy;
}

unique_ptr<Expression> Multiplication::copy(){
    vector<unique_ptr<Expression>> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Expression> ithCopy = move(operands[i]->copy());
        copiedContent.push_back(move(ithCopy));
    }

    if (root != nullptr & exponent != nullptr){
        return make_unique<Multiplication>(sign, root->copy(), exponent->copy(), copiedContent);
    }else if (root == nullptr & exponent != nullptr){
        return make_unique<Multiplication>(sign, nullptr, exponent->copy(), copiedContent);
    }else if (root != nullptr & exponent == nullptr){
        return make_unique<Multiplication>(sign, root->copy(), nullptr, copiedContent);
    }else{
        return make_unique<Multiplication>(sign, nullptr, nullptr, copiedContent);
    } 
}
#include "equationComponents.h"

Constant::Constant(): TermBase(){}

Constant::Constant(bool sign, TermBase* root, TermBase* exponent, int constant): TermBase(sign, root, exponent), constant(constant){
    updateExpressionString();
}

Constant::~Constant(){
    delete root;
    delete exponent;
    delete parentExpression;
}

void Constant::sanitiseForFactoring(){

}

bool Constant::isOne(){
    if (constant == 1){
        return true;
    }else{
        return false;
    }
}

bool Constant::isAtomic(){return true;}

bool Constant::isAtomicExponent(){
    if (constant == 1){
        return true;
    }else{
        return false;;
    }
}

bool Constant::isAtomicNumerator(){
    if (constant == 1){
        return true;
    }else{
        return false;;
    }
}

bool Constant::isLikeTerm(TermBase* other){
    if (!other->isAtomic()){
        return false;
    }else{
        Constant* constant = dynamic_cast<Constant*> (other);
        Variable* variable = dynamic_cast<Variable*> (other);
        if (constant){
            return true;
        }
        if (variable){
            return false;
        }
    }
}

bool Constant::isMergeable(){
    return true;
}

int* Constant::getValue(){
    return &constant;
}

TermBase* Constant::getAtom(){
    return this;
}

std::vector<TermBase*> Constant::getContent(){
    std::vector<TermBase*> content;
    content.push_back(this);
    return content;
}

TermBase* Constant::sum(TermBase* other){
    Constant* otherConstant = dynamic_cast<Constant*> (other);

    if (otherConstant){
        int newConstant = constant + otherConstant->getConstant();
        if (newConstant < 0){
            return new Constant(false, nullptr, nullptr, newConstant);
        }else{
            return new Constant(true, nullptr, nullptr, newConstant);
        }
    }else{
        TermContainer* newContainer = new TermContainer();
        newContainer->setOperationType(OperationType::Summation);
        newContainer->appendTerm(this);
        newContainer->appendTerm(other);
        return newContainer;
    }
}

TermBase* Constant::multiply(TermBase* other){
    Constant* otherConstant = dynamic_cast<Constant*> (other);

    if (otherConstant){
        int newConstant = constant * otherConstant->getConstant();
        if (newConstant < 0){
            return new Constant(false, nullptr, nullptr, newConstant);
        }else{
            return new Constant(true, nullptr, nullptr, newConstant);
        }
    }else{
        TermContainer* newContainer = new TermContainer();
        newContainer->setOperationType(OperationType::Multiplication);
        newContainer->appendTerm(this);
        newContainer->appendTerm(other);
        return newContainer;
    }
}

TermBase* Constant::divide(TermBase* other){
    Constant* otherConstant = dynamic_cast<Constant*> (other);

    if (otherConstant){
        int newConstant = constant / otherConstant->getConstant();
        if (newConstant < 0){
            return new Constant(false, nullptr, nullptr, newConstant);
        }else{
            return new Constant(true, nullptr, nullptr, newConstant);
        }
    }else{
        TermContainer* newContainer = new TermContainer();
        newContainer->setOperationType(OperationType::Division);
        newContainer->appendTerm(this);
        newContainer->appendTerm(other);
        return newContainer;
    }
}

TermBase* Constant::mergeMultiplications(TermBase* other){
    if (other->isMergeable()){

        std::vector<TermBase*> tmpTerms;
        tmpTerms.push_back(this);

        std::vector<TermBase*> otherTerms = other->getContent();
        for (int j = 0; j < otherTerms.size(); j ++){
            tmpTerms.push_back(otherTerms[j]);
        }
        return new TermContainer(true, nullptr, nullptr, OperationType::Multiplication, tmpTerms);
    }else{
        return nullptr;
    }
}

TermBase* Constant::expandForExponent(){
    if (!exponent){
        return this;
    }else{
        TermBase* expanded = exponent->expandAsExponent(this);
        expanded->sanitiseForFactoring();
        return expanded;
    }
}

TermBase* Constant::expandAsExponent(TermBase* baseTerm){
    TermContainer* expandedTerm = new TermContainer();
    expandedTerm->setOperationType(OperationType::Multiplication);

    if (!sign){
        expandedTerm = static_cast<TermContainer*> (expandAsNegativeExponent(baseTerm));
        return expandedTerm;
    }else{
        if (constant > 1){
            for (int i = 0; i < constant; i ++){
                TermBase* copiedBase = baseTerm->copy();
                copiedBase->setExponent(nullptr);
                expandedTerm->appendTerm(copiedBase);
            }
            return expandedTerm;
        }else{
            return this;
        }
    }
}

TermBase* Constant::expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational){

    TermContainer* expandedTerm = new TermContainer();
    expandedTerm->setOperationType(OperationType::Multiplication);

    // TermBase* newTerm = baseTerm->copy();
    // TermContainer* newExponent = static_cast<TermContainer*> (baseRational->copy());
    // newExponent->getTerms()[0] = new Constant(true, nullptr, nullptr, 1);
    // newTerm->setExponent(newExponent);

    std::vector<TermBase*> newExponentTerms = {new Constant(true, nullptr, nullptr, 1), baseRational->getTerms()[1]->copy()};
    TermContainer* newExponent = new TermContainer(true, nullptr, nullptr, OperationType::Division, newExponentTerms);
    TermBase* newTerm = baseTerm->copy();
    newTerm->setExponent(newExponent);


    for (int i = 0; i < constant; i ++){
        expandedTerm->appendTerm(newTerm->copy());
    }

    return expandedTerm;
}

TermBase* Constant::expandAsNegativeExponent(TermBase* baseTerm){
    TermContainer* expandedTerm = new TermContainer();
    expandedTerm->setOperationType(OperationType::Multiplication);

    for (int i = 0; i < constant; i ++){
        TermContainer* newRational = new TermContainer();
        newRational->setOperationType(OperationType::Division);

        TermBase* newDenom = baseTerm->copy();
        newDenom->setExponent(nullptr);
        newRational->appendTerm(new Constant(true, nullptr, nullptr, 1));
        newRational->appendTerm(newDenom);
        expandedTerm->appendTerm(newRational);
    }
    return expandedTerm;
}


TermBase* Constant::factor(){
    return this;
}

std::vector<TermBase*> Constant::getConstantFactors(){
    std::vector<TermBase*> constantFactors;
    for (int i = 1; i <= constant; i ++){
        if (constant % i == 0){
            Constant* factor = new Constant(true, nullptr, nullptr, i);
            constantFactors.push_back(factor);
        }
    }
    return constantFactors;
}

std::vector<TermBase*> Constant::getAllFactors(){

    std::vector<TermBase*> factors;
    std::vector<TermBase*> constantFactors = getConstantFactors();

    TermBase* expanded = expandForExponent();
    std::vector<TermBase*> expandedTerms = expanded->getContent();
    getAllSubTerms(expandedTerms, factors, 0, 0);

    for (TermBase* cf : constantFactors){
        factors.push_back(cf);
    }
    return factors;
}

TermBase* Constant::copy(){
    if (root != nullptr & exponent != nullptr){
        return new Constant(sign, root->copy(), exponent->copy(), constant);
    }else if (root == nullptr & exponent != nullptr){
        return new Constant(sign, nullptr, exponent->copy(), constant);
    }else if (root != nullptr & exponent == nullptr){
        return new Constant(sign, root->copy(), nullptr, constant);
    }else{
        return new Constant(sign, nullptr, nullptr, constant);
    }
    
}

std::string Constant::toString(){
    std::string termStr = "";
    if (!sign){
        termStr += '-';
    }

    termStr += std::to_string(constant);

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

std::string Constant::exponentToString(){
    return "^(" + this->toString() + ')';
}
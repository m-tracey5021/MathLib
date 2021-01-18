#include "equationComponents.h"

Variable::Variable(): TermBase(){}

Variable::Variable(bool sign, TermBase* root, TermBase* exponent, char variable): TermBase(sign, root, exponent), variable(variable){
    updateExpressionString();
}

Variable::~Variable(){
    delete root;
    delete exponent;
    delete parentExpression;
}

void Variable::sanitiseForFactoring(){

}



bool Variable::isOne(){return false;}

bool Variable::isAtomic(){return true;}

bool Variable::isAtomicExponent(){return true;}

bool Variable::isAtomicNumerator(){return true;}

bool Variable::isLikeTerm(TermBase* other){
    if (!other->isAtomic()){
        return false;
    }else{
        Constant* otherConstant = dynamic_cast<Constant*> (other);
        Variable* otherVariable = dynamic_cast<Variable*> (other);
        if (otherConstant){
            return false;
        }
        if (otherVariable){
            return true;
        }
    }
}

bool Variable::isMergeable(){
    return true;
}

int* Variable::getValue(){
    return nullptr;
}

TermBase* Variable::getAtom(){
    return this;
}

std::vector<TermBase*> Variable::getContent(){
    std::vector<TermBase*> content;
    content.push_back(this);
    return content;
}

TermBase* Variable::sum(TermBase* other){
    Variable* otherVariable = dynamic_cast<Variable*> (other);

    TermContainer* newContainer = new TermContainer();

    if (otherVariable){
        if (otherVariable->getVariable() == variable){
            Constant* newCoefficient = new Constant(true, nullptr, nullptr, 2);
            newContainer->setOperationType(OperationType::Multiplication);
            newContainer->appendTerm(newCoefficient);
            newContainer->appendTerm(otherVariable);
            return newContainer;
        }else{
            newContainer->setOperationType(OperationType::Summation);
            newContainer->appendTerm(this);
            newContainer->appendTerm(otherVariable);
            return newContainer;
        }
    }else{
        newContainer->setOperationType(OperationType::Summation);
        newContainer->appendTerm(this);
        newContainer->appendTerm(other);
        return newContainer;
    }
}

TermBase* Variable::multiply(TermBase* other){
    Variable* otherVariable = dynamic_cast<Variable*> (other);

    TermContainer* newContainer = new TermContainer();

    if (otherVariable){
        if (otherVariable->getVariable() == variable){
            Constant* exponent = new Constant(true, nullptr, nullptr, 2);
            Variable* newVariable;
            if (sign != otherVariable->getSign()){
                newVariable = new Variable(false, nullptr, exponent, variable);
            }else{
                newVariable = new Variable(true, nullptr, exponent, variable);
            }
            return newVariable;
        }else{
            newContainer->setOperationType(OperationType::Multiplication);
            newContainer->appendTerm(this);
            newContainer->appendTerm(otherVariable);
            return newContainer;
        }
    }else{
        newContainer->setOperationType(OperationType::Multiplication);
        newContainer->appendTerm(this);
        newContainer->appendTerm(other);
        return newContainer;
    }
}

TermBase* Variable::divide(TermBase* other){
    Variable* otherVariable = dynamic_cast<Variable*> (other);

    TermContainer* newContainer = new TermContainer();

    if (otherVariable){
        if (otherVariable->getVariable() == variable){
            Constant* one;
            if (sign != otherVariable->getSign()){
                one = new Constant(false, nullptr, nullptr, 1);
            }else{
                one = new Constant(true, nullptr, nullptr, 1);
            }
            return one;
        }else{
            newContainer->setOperationType(OperationType::Division);
            newContainer->appendTerm(this);
            newContainer->appendTerm(otherVariable);
            return newContainer;
        }
    }else{
        newContainer->setOperationType(OperationType::Division);
        newContainer->appendTerm(this);
        newContainer->appendTerm(other);
        return newContainer;
    }
}

TermBase* Variable::mergeMultiplications(TermBase* other){
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

TermBase* Variable::expandForExponent(){
    if (!exponent){
        return this;
    }else{
        TermBase* expanded = exponent->expandAsExponent(this);
        expanded->sanitiseForFactoring();
        return expanded;
    }
}

TermBase* Variable::expandAsExponent(TermBase* baseTerm){
    return baseTerm;
}

TermBase* Variable::expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational){
    return nullptr;
}

TermBase* Variable::expandAsNegativeExponent(TermBase* baseTerm){
    return baseTerm;
}

TermBase* Variable::factor(){
    if (exponent != nullptr){
        if (!exponent->isOne()){
            Constant* constantExponent = dynamic_cast<Constant*> (exponent);
            Variable* variableExponent = dynamic_cast<Variable*> (exponent);
            TermContainer* containerExponent = dynamic_cast<TermContainer*> (exponent);

            if (constantExponent){
                for (int i = 0; i < constantExponent->getConstant(); i ++){

                }
            }else if (variableExponent){

            }else if (containerExponent){

            }else{
                // throw error
            }
            // find all things which add together to equal the target exponent, but they cannot be rationals
        }else{
            return this;
        }
    }else{
        return this;
    }
}

std::vector<TermBase*> Variable::getConstantFactors(){
    std::vector<TermBase*> constantFactors;
    return constantFactors;
}

std::vector<TermBase*> Variable::getAllFactors(){

    std::vector<TermBase*> factors;
    std::vector<TermBase*> expandedTerms = expandForExponent()->getContent();
    getAllSubTerms(expandedTerms, factors, 0, 0);

    return factors;

}

TermBase* Variable::copy(){
    if (root != nullptr & exponent != nullptr){
        return new Variable(sign, root->copy(), exponent->copy(), variable);
    }else if (root == nullptr & exponent != nullptr){
        return new Variable(sign, nullptr, exponent->copy(), variable);
    }else if (root != nullptr & exponent == nullptr){
        return new Variable(sign, root->copy(), nullptr, variable);
    }else{
        return new Variable(sign, nullptr, nullptr, variable);
    }
}

std::string Variable::toString(){
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

std::string Variable::exponentToString(){
    return "^(" + this->toString() + ')';
}
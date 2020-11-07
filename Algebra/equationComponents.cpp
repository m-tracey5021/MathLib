
#include "equationComponents.h"


// ===== CONSTANT =====


Constant::Constant(): TermBase(){}

Constant::Constant(bool sign, TermBase* root, TermBase* exponent, int constant): TermBase(sign, root, exponent), constant(constant){
    updateExpressionString();
}

Constant::~Constant(){
    delete root;
    delete exponent;
    delete parentExpression;
}

bool Constant::isOne(){
    if (constant == 1){
        return true;
    }else{
        return false;
    }
}

bool Constant::isAtomic(){return true;}

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

TermBase* Constant::factor(){
    return this;
}

std::vector<TermBase*> Constant::allFactors(){
    std::vector<TermBase*> factors;
    for (int i = 0; i <= constant; i ++){
        if (constant % i == 0){
            Constant* factor = new Constant(true, nullptr, nullptr, i);
            factors.push_back(factor);
        }
    }
    return factors;
}

std::vector<TermBase*> Constant::allComponents(){

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
            if (exponent->getSign()){
                termStr = termStr + "^(" + exponent->toString() + ')';
            }else{
                termStr = termStr + "^" + exponent->toString();
            }
        }
    }
    return termStr;
}


// ===== VARIABLE =====


Variable::Variable(): TermBase(){}

Variable::Variable(bool sign, TermBase* root, TermBase* exponent, char variable): TermBase(sign, root, exponent), variable(variable){
    updateExpressionString();
}

Variable::~Variable(){
    delete root;
    delete exponent;
    delete parentExpression;
}

bool Variable::isOne(){return false;}

bool Variable::isAtomic(){return true;}

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
    }
}

std::vector<TermBase*> Variable::allFactors(){
    std::vector<TermBase*> factors;
    if (exponent != nullptr){
        if (!exponent->isOne()){
            Constant* constantExponent = dynamic_cast<Constant*> (exponent);
            Variable* variableExponent = dynamic_cast<Variable*> (exponent);
            TermContainer* containerExponent = dynamic_cast<TermContainer*> (exponent);

            if (constantExponent){
                for (int i = 1; i <= constantExponent->getConstant(); i ++){
                    Constant* componentExponent = new Constant(true, nullptr, nullptr, i);
                    Variable* posVariableFactor = new Variable(true, nullptr, componentExponent, variable);
                    factors.push_back(posVariableFactor);
                    if (!sign){
                        Variable* negVariableFactor = new Variable(false, nullptr, componentExponent, variable);
                        factors.push_back(negVariableFactor);
                    }

                }
            }else if (variableExponent){
                factors.push_back(this);
            }else if (containerExponent){
                /*
                find all possible ways to sum
                to the target exponenet, only using
                whole numbers
                */

            }else{
                // throw error
            }
        }else{
            factors.push_back(this);
        } 
    }
    return factors;
}

std::vector<TermBase*> Variable::allComponents(){
    std::vector<TermBase*> components;
    components.push_back(this);
    return components;
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
            if (exponent->getSign()){
                termStr = termStr + "^(" + exponent->toString() + ')';
            }else{
                termStr = termStr + "^" + exponent->toString();
            }
            
        }
    }

    return termStr;
}


// ===== TERMCONTAINER =====



TermContainer::TermContainer(): TermBase(){
    coefficient = new Constant(true, nullptr, nullptr, 1);
    updateExpressionString();
}

TermContainer::TermContainer(bool sign, TermBase* root, TermBase* exponent, Constant* coefficient): TermBase(sign, root, exponent), coefficient(coefficient){
    updateExpressionString();
}

TermContainer::~TermContainer(){
    delete root;
    delete exponent;
    delete parentExpression;
}

std::vector<TermBase*> TermContainer::getTerms(){return terms;}

OperationType TermContainer::getOperationType(){return operationType;}

Constant* TermContainer::getCoefficient(){return coefficient;}

void TermContainer::setTerms(std::vector<TermBase*> t){terms = t; updateExpressionString();}

void TermContainer::setOperationType(OperationType o){operationType = o; updateExpressionString();}

void TermContainer::setCoefficient(Constant* c){coefficient = c; updateExpressionString();}

void TermContainer::appendTerm(TermBase* t){terms.push_back(t); t->setParentExpression(this); updateExpressionString();}

void TermContainer::removeTerm(int i){terms.erase(terms.begin() + i); updateExpressionString();}

bool TermContainer::isOne(){
    if (terms.size() == 1 & terms[0]->isOne()){
        return true;
    }else{
        return false;
    }
}

bool TermContainer::isAtomic(){
    if (terms.size() == 1 & terms[0]->isAtomic()){
        return true;
    }else{
        return false;
    }
}

bool TermContainer::isLikeTerm(TermBase* other){
    TermContainer* otherContainer = dynamic_cast<TermContainer*> (other);

    if (otherContainer){
        if (operationType != otherContainer->getOperationType()){
            return false;
        }else{
            if (operationType == OperationType::Multiplication){ // only need to check one operationType because we know both are the same if this if-block is entered
                int indexThis;
                int indexOther;

                coefficient->isOne() ? indexThis = 0 : indexThis = 1;
                otherContainer->getCoefficient()->isOne() ? indexOther = 0: indexOther = 1;
                
                if (terms.size() - indexThis != otherContainer->getTerms().size() - indexOther){ // if the two terms are different sizes, they cant be added
                    return false;
                }else{
                    bool termsEqual = true;
                    while (termsEqual){ // make sure loop doesnt continue past the end of terms
                        if (!terms[indexThis]->isEqual(otherContainer->getTerms()[indexOther])){
                            termsEqual = false;
                        }
                        indexThis ++;
                        indexOther ++;
                    }
                    return termsEqual; // return true if all components are the same, false if else
                }
                
                
            }else if (operationType == OperationType::Division){
                if (terms[1]->isLikeTerm(otherContainer->getTerms()[1])){ // if denom is the same, return true, they two numerators can be added
                    return true;
                }else{
                    return false;
                }
            }else{ // you can always add one polynomial to another, just end up with a bigger polynomial, program this elsewhere
                if (terms.size() != otherContainer->getTerms().size()){
                    return false;
                }else{
                    bool termsEqual = true;
                    for (int i = 0; i < terms.size(); i ++){
                        if (!terms[i]->isLikeTerm(otherContainer->getTerms()[i])){
                            termsEqual = false;
                        }
                    }
                    return termsEqual;
                }
            }
        }
    }else{
        return false;
    }
}

TermBase* TermContainer::sum(TermBase* other){
    return nullptr;
}

TermBase* TermContainer::multiply(TermBase* other){
    return nullptr;
}


TermBase* TermContainer::divide(TermBase* other){
    return nullptr;
}


TermBase* TermContainer::factor(){
    TermContainer* factoredContainer = new TermContainer();

    if (operationType == OperationType::Multiplication){
        factoredContainer->setOperationType(OperationType::Multiplication);
        for (int i = 0; i < terms.size(); i ++){
            TermBase* factoredTerm = terms[i]->factor();
            factoredContainer->appendTerm(factoredTerm);
        }
    }else if (operationType == OperationType::Division){
        factoredContainer->setOperationType(OperationType::Division);
        for (int i = 0; i < terms.size(); i ++){
            TermBase* factoredTerm = terms[i]->factor();
            factoredContainer->appendTerm(factoredTerm);
        }
    }else{
        factoredContainer->setOperationType(OperationType::Summation);

    }
    return this;
}

std::vector<TermBase*> TermContainer::allFactors(){
    std::vector<TermBase*> dummy;
    return dummy;
}

std::vector<TermBase*> TermContainer::allComponents(){
    std::vector<TermBase*> components;
    for (int i = 0; i < terms.size(); i ++){
        std::vector<TermBase*> subComponents = terms[i]->allComponents();
        for(int j = 0; j < subComponents.size(); j ++){
            components.push_back(subComponents[j]);
        }
    }
    return components;
}

std::string TermContainer::toString(){
    std::string termStr = "";
    if (operationType == OperationType::Multiplication){
        for (int i = 0; i < terms.size(); i ++){
            termStr += terms[i]->toString();
        }
        if (!sign){
            termStr = '-' + termStr;
        }
    }else if (operationType == OperationType::Division){
        for (int i = 0; i < terms.size(); i ++){
            if (i == terms.size() - 1){
                termStr += terms[i]->toString();
            }else{
                termStr += terms[i]->toString() + '/';
            }
            
        }
        if (!sign){
            termStr = "-{" + termStr + '}';
        }else{
            termStr = '{' + termStr + '}';
        }
    }else{
        for (int i = 0; i < terms.size(); i ++){
            if (i == 0){
                termStr += terms[i]->toString();
            }else{
                if (terms[i]->getSign()){
                    termStr += '+' + terms[i]->toString();
                }else{
                    termStr += '-' + terms[i]->toString();
                }
            }
        }
        if (!sign){
            termStr = "-(" + termStr + ')';
        }else{
            if (terms.size() != 1 & parentExpression != nullptr){
                termStr = '(' + termStr + ')';
            }
        }
    }

    if (root != nullptr){
        if (!root->isOne()){
            termStr = '[' + root->toString() + '|' + termStr + ']';
        }
    }
    if (exponent != nullptr){
        if (!exponent->isOne()){
            if (exponent->getSign()){
                termStr = termStr + "^(" + exponent->toString() + ')';
            }else{
                termStr = termStr + '^' + exponent->toString();
                
            }
        }
    }
    return termStr;
}
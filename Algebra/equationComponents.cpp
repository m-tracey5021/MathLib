
#include "equationComponents.h"
#include <algorithm>
#include <cmath>

// ===== UTIL =====

std::pair<TermBase*, TermBase*> getZeroSum(TermBase* sumTarget){
    std::pair<TermBase*, TermBase*> zeroSum;
    Constant* zero = new Constant(true, nullptr, nullptr, 0);
    zeroSum.first = zero;
    zeroSum.second = sumTarget;
    return zeroSum;

}

// ===== TERMBASE =====

TermBase::TermBase(): 
                sign(true), 
                root(nullptr), 
                exponent(nullptr),
                parentExpression(nullptr){}

TermBase::TermBase(bool sign, TermBase* root, TermBase* exponent): 
                sign(sign), 
                root(root), 
                exponent(exponent), 
                parentExpression(nullptr){}

bool TermBase::getSign(){
    return sign;
}

TermBase* TermBase::getRoot(){
    return root;
}

TermBase* TermBase::getExponent(){
    return exponent;
}

TermBase* TermBase::getParentExpression(){
    return parentExpression;
}

std::string TermBase::getExpressionString(){
    return expressionString;
}

void TermBase::setSign(bool s){
    sign = s; 
    updateExpressionString();
}

void TermBase::setRoot(TermBase* r){
    root = r; 
    parentExpression = r;
    updateExpressionString();
}

void TermBase::setExponent(TermBase* e){
    exponent = e; 
    updateExpressionString();
}

void TermBase::setParentExpression(TermBase* p){
    if (p != nullptr){
        parentExpression = p;
    }
    
}

void TermBase::updateExpressionString(){
    if (parentExpression){
        parentExpression->updateExpressionString();
    }
    expressionString = this->toString();
}

bool TermBase::isEqual(TermBase* other){
    if (expressionString == other->getExpressionString()){
        return true;
    }else{
        return false;
    }
}


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

void Constant::sanitise(){

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

TermBase* Constant::expandForExponent(){
    if (!exponent){
        return nullptr;
    }else{
        return exponent->expandAsExponent(this);
    }
}

TermBase* Constant::expandAsExponent(TermBase* baseTerm){
    TermContainer* expandedTerm = new TermContainer();
    expandedTerm->setOperationType(OperationType::Multiplication);

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

TermBase* Constant::expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational){

    TermContainer* expandedTerm = new TermContainer();
    expandedTerm->setOperationType(OperationType::Multiplication);

    TermBase* newTerm = baseTerm->copy();
    TermContainer* newExponent = static_cast<TermContainer*> (baseRational->copy());
    newExponent->getTerms()[0] = new Constant(true, nullptr, nullptr, 1);
    newTerm->setExponent(newExponent);

    for (int i = 0; i < constant; i ++){
        expandedTerm->appendTerm(newTerm->copy());
    }

    return expandedTerm;
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
    if (!sign & parentExpression == nullptr){
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

void Variable::sanitise(){

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

TermBase* Variable::expandForExponent(){
    if (!exponent){
        return nullptr;
    }else{
        return exponent->expandAsExponent(this);
    }
}

TermBase* Variable::expandAsExponent(TermBase* baseTerm){
    return baseTerm;
}

TermBase* Variable::expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational){
    return nullptr;
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

std::vector<TermBase*> Variable::allFactors(){
    std::vector<TermBase*> factors;
    
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
    if (!sign & parentExpression == nullptr){
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



// ===== TERMCONTAINER =====



TermContainer::TermContainer(): TermBase(){
    //coefficient = new Constant(true, nullptr, nullptr, 1);
    updateExpressionString();
}

TermContainer::TermContainer(bool sign, TermBase* root, TermBase* exponent): TermBase(sign, root, exponent){
    updateExpressionString();
}

TermContainer::TermContainer(bool sign, TermBase* root, TermBase* exponent, OperationType operationType, std::vector<TermBase*> terms): TermBase(sign, root, exponent), operationType(operationType), terms(terms){
    for (TermBase* t : terms){
        t->setParentExpression(this);
    }
    updateExpressionString();
}

TermContainer::~TermContainer(){
    delete root;
    delete exponent;
    delete parentExpression;
}

// Constant* TermContainer::getCoefficient(){return coefficient;}

OperationType TermContainer::getOperationType(){return operationType;}

std::vector<TermBase*> TermContainer::getTerms(){return terms;}

std::vector<TermBase*> TermContainer::duplicateTerms(int start, int end){
    std::vector<TermBase*> duplicated;
    for (int i = start; i <= end; i ++){
        duplicated.push_back(terms[i]->copy());
    }
    return duplicated;
}

/*
void TermContainer::setCoefficient(Constant* c){
    if (c->getConstant() == 1){
        if (coefficient->getConstant() != 1){
            terms.erase(terms.begin());
        }
    }else{
        if (coefficient->getConstant() == 1){
            terms.insert(terms.begin(), c);
        }else{
            terms.insert(terms.begin(), c);
            terms.erase(terms.begin() + 1);
        }
    }
    
    coefficient = c;
    updateExpressionString();
}
*/

void TermContainer::setOperationType(OperationType o){operationType = o; updateExpressionString();}

void TermContainer::setTerms(std::vector<TermBase*> t){
    terms = t;
    for (TermBase* term : terms){
        term->setParentExpression(this);
    }
    updateExpressionString();}

void TermContainer::appendTerm(TermBase* t){
    terms.push_back(t);
    t->setParentExpression(this);
    updateExpressionString();
}

void TermContainer::removeTerm(int i){terms.erase(terms.begin() + i); updateExpressionString();}

void TermContainer::replaceTerm(int i, TermBase* t){terms.insert(terms.begin() + i, t); removeTerm(i + 1);}

void TermContainer::sanitise(){
    std::vector<TermBase*> sanitised;

    if (operationType == OperationType::Multiplication){
        // make one term out of several multiplicative terms
        for (int i = 0; i < terms.size(); i++){
            TermBase* parent = terms[i];
            for (int j = 0; j < parent->getContent().size(); j ++){
                TermBase* child = parent->getContent()[j];
                sanitised.push_back(child);
            }
        }
        // update coefficient
        int totalCoeff = 0;
        for (int i = 0; i < sanitised.size(); i ++){
            TermBase* current = sanitised[i];
            int* valPtr = current->getValue();
            if (valPtr){
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
            Constant* coeff = new Constant(true, nullptr, nullptr, totalCoeff);
            sanitised.insert(sanitised.begin(), coeff);
        }
        terms = sanitised;
    }else if (operationType == OperationType::Division){

    }else{

    }
}

bool TermContainer::isOne(){
    if (terms.size() == 1){
        if (terms[0]->isOne()){
            return true;
        }
        return false;
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

bool TermContainer::isAtomicExponent(){
    if (terms.size() > 1){
        if (operationType == OperationType::Summation){
            return false;
        }else if (operationType == OperationType::Multiplication){
            // return true, only if all the terms in the multiplication are variables
            if (terms[0]->getValue() != nullptr){
                return false;
            }else{
                return true;
            }
        }else{
            if (terms[0]->isAtomicNumerator()){
                return true;
            }else{
                return false;
            }
        }
    }else{
        if (terms[0]->isAtomicExponent()){
            return true;
        }else{
            return false;
        } 
    }   
}

bool TermContainer::isAtomicNumerator(){return false;}

bool TermContainer::isLikeTerm(TermBase* other){
    /*
    TermContainer* otherContainer = dynamic_cast<TermContainer*> (other);

    if (otherContainer){
        if (operationType != otherContainer->getOperationType()){
            return false;
        }else{
            if (operationType == OperationType::Multiplication){ // only need to check one operationType because we know both are the same if this if-block is entered
                int indexThis;
                int indexOther;

                // if (terms[0]->isOne())

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
    */
   return false; // REMEMBER TO REMOVE THIS
}

int* TermContainer::getValue(){
    return nullptr; 
    // eventually update this to add or solve
}

TermBase* TermContainer::getAtom(){
    if (isAtomic()){
        return terms[0]->getAtom();
    }else{
        return nullptr;
    }
    
}

std::vector<TermBase*> TermContainer::getContent(){
    return terms;
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

TermBase* TermContainer::expandForExponent(){
    // rewrite this when parsing function has een completed properly
    /*
    TermBase* expandedTerm;
    if (!exponent){
        if (terms.size() == 1){
            TermBase* atom = getAtom();
            TermBase* atomExponent = atom->getExponent();
            if (atomExponent){
                expandedTerm = atomExponent->expandAsExponent(atom);
            }
            
        }
    }else{
        expandedTerm = exponent->expandAsExponent(this);
    }
    
    return expandedTerm;
    */
    if (!exponent){
        return nullptr;
    }else{
        return exponent->expandAsExponent(this);
    }
}

TermBase* TermContainer::expandAsExponent(TermBase* baseTerm){

    sanitise();
    
    TermBase* expandedAtomic = nullptr;
    TermContainer* expandedTerm = new TermContainer();
    expandedTerm->setOperationType(OperationType::Multiplication);

    // expand the exponents of the innerTerms

    TermContainer* tmpExponent = static_cast<TermContainer*> (this->copy());
    std::vector<TermBase*> tmpTerms = tmpExponent->getTerms();

    for (int i = 0; i < tmpTerms.size(); i ++){
        TermBase* innerTerm = tmpTerms[i];
        TermBase* innerExponent = innerTerm->getExponent();
        if (innerExponent != nullptr){
            if (!innerExponent->isAtomicExponent()){
                TermBase* expandedInnerTerm = innerTerm->expandForExponent();
                tmpExponent->replaceTerm(i, expandedInnerTerm);
            }
        }
    }
    
    // expand the exponent of the main exponent

    if (tmpExponent->getExponent() != nullptr){
        tmpExponent = static_cast<TermContainer*> (tmpExponent->expandForExponent());
        
    }
    tmpTerms = tmpExponent->getTerms();

    // expand the main exponent over the baseTerm passed in

    if (isAtomic()){
        expandedAtomic = getAtom()->expandAsExponent(baseTerm);
    }else{
        if (operationType == OperationType::Multiplication){

            int* coeffPtr = terms[0]->getValue();

            if (coeffPtr){
                int coeff = *coeffPtr;
                TermBase* newTerm = baseTerm->copy();
                TermContainer* newExponent = static_cast<TermContainer*> (tmpExponent->copy());
                newExponent->removeTerm(0);
                newTerm->setExponent(newExponent);

                for (int i = 0; i < coeff; i ++){
                    expandedTerm->appendTerm(newTerm->copy());
                }
            }
        }else if (operationType == OperationType::Division){
            TermBase* numerator = tmpExponent->getTerms()[0];
            expandedTerm = static_cast<TermContainer*> (numerator->expandAsConstNum(baseTerm, tmpExponent));

        }else{
            for (int i = 0; i < tmpTerms.size(); i ++){

                TermBase* newTerm = baseTerm->copy();
                TermBase* newExponent = tmpTerms[i]->copy();
                newTerm->setExponent(newExponent);
                expandedTerm->appendTerm(newTerm);
            }
        }
    }

    

    /* 
        check that the resultant expandedTerm is fully expanded, i.e. all
        of the exponents are in atomic form, either 1 or n or 1/n 
    */

    if (!expandedAtomic){
        if (expandedTerm->getTerms().size() == 0){
            return this;
        }else{
            for (int i = 0; i < expandedTerm->getTerms().size(); i ++){
                TermBase* ithExpandedTerm = expandedTerm->getTerms()[i];
                TermBase* ithExponent = ithExpandedTerm->getExponent();
                if (!ithExponent->isAtomicExponent()){
                    expandedTerm->replaceTerm(i, ithExpandedTerm->expandForExponent());
                }
            }
            return expandedTerm;
        }
        
    }else{
        return expandedAtomic;
    }
}

TermBase* TermContainer::expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational){
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

TermBase* TermContainer::copy(){
    //Constant* newCoefficient = dynamic_cast<Constant*> (coefficient->copy());
    std::vector<TermBase*> newTerms;
    for (int i = 0; i < terms.size(); i ++){
        TermBase* newTerm = terms[i]->copy();
        newTerms.push_back(newTerm);
    }

    if (root != nullptr & exponent != nullptr){
        return new TermContainer(sign, root->copy(), exponent->copy(), operationType, newTerms);
    }else if (root == nullptr & exponent != nullptr){
        return new TermContainer(sign, nullptr, exponent->copy(), operationType, newTerms);
    }else if (root != nullptr & exponent == nullptr){
        return new TermContainer(sign, root->copy(), nullptr, operationType, newTerms);
    }else{
        return new TermContainer(sign, nullptr, nullptr, operationType, newTerms);
    } 
}

std::string TermContainer::toString(){
    
    std::string termStr = "";
    if (operationType == OperationType::Multiplication){
        /*
        if (coefficient->getConstant() != 1){
            termStr += coefficient->toString();
        }
        */
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
                    termStr += terms[i]->toString();
                }
            }
        }
        if (!sign){
            termStr = "-(" + termStr + ')';
        }else{
            if ((terms.size() != 1 & parentExpression != nullptr) | exponent != nullptr){
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
            termStr = termStr + exponent->exponentToString();
        }
    }
    return termStr;
}

std::string TermContainer::exponentToString(){
    std::string termStr = this->toString();
    if (sign){
        return "^(" + termStr + ')';
    }else{
        return '^' + termStr;
    }
    return this->toString();
}
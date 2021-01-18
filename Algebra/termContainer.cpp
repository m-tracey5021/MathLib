#include "equationComponents.h"

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

void TermContainer::sanitiseForFactoring(){
    std::vector<TermBase*> sanitised;

    if (operationType == OperationType::Multiplication){
        // make one term out of several multiplicative terms
        TermBase* merged = nullptr;
        for (int i = 1; i < terms.size(); i++){
            if (!merged){
                merged = terms[0]->mergeMultiplications(terms[i]);
            }else{
                merged = merged->mergeMultiplications(terms[i]);
            }

            // TermBase* parent = terms[i];
            // for (int j = 0; j < parent->getContent().size(); j ++){
            //     TermBase* child = parent->getContent()[j];
            //     sanitised.push_back(child);
            // }
        }

        if (!merged){
            sanitised = terms;
        }else{
            sanitised = merged->getContent();
        }
        
        // update coefficient
        int totalCoeff = 0;
        for (int i = 0; i < sanitised.size(); i ++){
            TermBase* current = sanitised[i];
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

bool TermContainer::isMergeable(){
    if (operationType == OperationType::Multiplication){
        return true;
    }else{
        return false;
    }
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

TermBase* TermContainer::mergeMultiplications(TermBase* other){
    if (operationType == OperationType::Multiplication & other->isMergeable()){
        std::vector<TermBase*> tmpTerms;
        for (int i = 0; i < terms.size(); i ++){
            tmpTerms.push_back(terms[i]);
        }
        std::vector<TermBase*> otherTerms = other->getContent();
        for (int j = 0; j < otherTerms.size(); j ++){
            tmpTerms.push_back(otherTerms[j]);
        }
        return new TermContainer(true, nullptr, nullptr, OperationType::Multiplication, tmpTerms);
    }else{
        return nullptr;
    }
    
}

TermBase* TermContainer::expandForExponent(){
    if (!exponent){
        return this;
    }else{
        TermBase* expanded = exponent->expandAsExponent(this);
        expanded->sanitiseForFactoring();
        return expanded;
    }
}

TermBase* TermContainer::expandAsExponent(TermBase* baseTerm){

    sanitiseForFactoring();
    
    //TermBase* expandedAtomic = nullptr;
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

    if (!sign){
        expandedTerm = static_cast<TermContainer*> (expandAsNegativeExponent(baseTerm));
    }else{
        if (isAtomicExponent()){
            return baseTerm;
        }else if (isAtomic() & !isAtomicExponent()){
            expandedTerm = static_cast<TermContainer*> (expandAsExponent(baseTerm));
        }else{
            
            if (operationType == OperationType::Multiplication){

                int* coeffPtr = terms[0]->getValue();

                if (coeffPtr){
                    int coeff = *coeffPtr;
                    TermBase* newTerm = baseTerm->copy();
                    TermContainer* newExponent = static_cast<TermContainer*> (tmpExponent->copy());
                    newExponent->removeTerm(0);
                    if (newExponent->getTerms().size() == 1){
                        TermBase* singleExponent = newExponent->getTerms()[0];
                        singleExponent->setParentExpression(nullptr);
                        newTerm->setExponent(singleExponent);
                    }else{
                        newTerm->setExponent(newExponent);
                    }
                    
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
    }
    

    

    /* 
        check that the resultant expandedTerm is fully expanded, i.e. all
        of the exponents are in atomic form, either 1 or n or nm or 1/n 
    */

    if (expandedTerm->getTerms().size() == 0){
        return this;
    }else{
        for (int i = 0; i < expandedTerm->getTerms().size(); i ++){
            TermBase* ithExpandedTerm = expandedTerm->getTerms()[i];
            expandedTerm->replaceTerm(i, ithExpandedTerm->expandForExponent()); // this is very inefficient
        }
        return expandedTerm;
    }

    /*
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
            //sanitise();
            std::string test = expandedTerm->toString();
            return expandedTerm;
        }
        
    }else{
        return expandedAtomic;
    }
    */
}

TermBase* TermContainer::expandAsConstNum(TermBase* baseTerm, TermContainer* baseRational){
    return baseTerm;
}

TermBase* TermContainer::expandAsNegativeExponent(TermBase* baseTerm){
    return baseTerm;
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

std::vector<TermBase*> TermContainer::getConstantFactors(){
    std::vector<TermBase*> constantFactors;
    if (operationType == OperationType::Multiplication){
        constantFactors = terms[0]->getConstantFactors();
    }else if (operationType == OperationType::Division){

    }else{
        for (TermBase* t : terms){
            std::vector<TermBase*> tConstantFactors = t->getConstantFactors();
            constantFactors.insert(constantFactors.end(), tConstantFactors.begin(), tConstantFactors.end());
        }
    }
    
    return constantFactors;
}

std::vector<TermBase*> TermContainer::getAllFactors(){
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
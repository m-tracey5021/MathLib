#include "expression.h"
#include "expressionFactory.h"

Multiplication::Multiplication(): Expression(){}

Multiplication::Multiplication(bool sign, 
                        ExpressionPtr& root, 
                        ExpressionPtr& exponent, 
                        vector<ExpressionPtr>& operands): 
                        Expression(sign, root, exponent), operands(move(operands)){}

// Multiplication::~Multiplication(){
//     root.reset();
//     exponent.reset();
//     parentExpression.reset();
//     delete &root;
//     delete &exponent;
//     delete &parentExpression;
//     operands.clear();
//     delete &operands;
// }

vector<ExpressionPtr> Multiplication::getOperands(){
    return move(operands);
}

void Multiplication::setOperands(vector<ExpressionPtr>& o){
    operands = move(o);
}

IntPtr Multiplication::getValue(){
    IntPtr empty = IntPtr();
    return empty;
}

vector<ExpressionPtr> Multiplication::getContent(){
    return move(operands);
}

void Multiplication::appendExpression(Expression& e){
    ExpressionPtr toAppend = ExpressionPtr(&e);
    ExpressionPtr thisPtr = ExpressionPtr(this);
    operands.push_back(move(toAppend));
    e.setParentExpression(thisPtr);
    updateExpressionString();
}

void Multiplication::removeExpression(int i){operands.erase(operands.begin() + i); updateExpressionString();}

void Multiplication::replaceExpression(int i, Expression& e){
    ExpressionPtr toReplace = ExpressionPtr(&e);
    operands.insert(operands.begin() + i, move(toReplace));
    removeExpression(i + 1);
}

void Multiplication::sanitise(){
    // make one term out of several multiplicative terms
    vector<ExpressionPtr> sanitised;
    ExpressionPtr merged;
    for (int i = 1; i < operands.size(); i++){
        if (!merged){
            merged = operands[0]->mergeMultiplications(*operands[i]);
        }else{
            merged = merged->mergeMultiplications(*operands[i]);
        }
    }

    if (!merged){
        sanitised = move(operands);
    }else{
        sanitised = merged->getContent();
    }
    
    // update coefficient
    int totalCoeff = 0;
    for (int i = 0; i < sanitised.size(); i ++){
        ExpressionPtr current = move(sanitised[i]);
        IntPtr valPtr = current->getValue();
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
        ExpressionFactory factory;
        ExpressionPtr coeff = factory.sign(true).root(nullptr).exponent(nullptr).constant(totalCoeff).buildConstantExpression().get();
        //ExpressionPtr coeff = make_unique<ConstantExpression>(true, nullptr, nullptr, totalCoeff);
        sanitised.insert(sanitised.begin(), move(coeff));
    }
    operands = move(sanitised);
}

bool Multiplication::isEqual(Expression& other){return other.isEqual(*this);}

bool Multiplication::isEqual(Summation& other){return false;}

bool Multiplication::isEqual(Multiplication& other){
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

bool Multiplication::isEqual(Division& other){return false;}

bool Multiplication::isEqual(ConstantExpression& other){return false;}

bool Multiplication::isEqual(VariableExpression& other){return false;}

bool Multiplication::isOne(){return false;}

bool Multiplication::isAtomic(){return false;}

bool Multiplication::isAtomicExponent(){return false;}

bool Multiplication::isAtomicNumerator(){return false;}

bool Multiplication::isLikeExpression(Expression& e){return false;}

bool Multiplication::isMergeable(){return false;}

ExpressionPtr Multiplication::sum(Summation& s){
    return nullptr;
}

ExpressionPtr Multiplication::sum(Multiplication& m){
    return nullptr;
}

ExpressionPtr Multiplication::sum(Division& d){
    return nullptr;
}

ExpressionPtr Multiplication::sum(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr Multiplication::sum(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr Multiplication::multiply(Summation& m){
    return nullptr;
}

ExpressionPtr Multiplication::multiply(Multiplication& m){
    return nullptr;
}

ExpressionPtr Multiplication::multiply(Division& d){
    return nullptr;
}

ExpressionPtr Multiplication::multiply(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr Multiplication::multiply(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr Multiplication::divide(Summation& m){
    return nullptr;
}

ExpressionPtr Multiplication::divide(Multiplication& m){
    return nullptr;
}

ExpressionPtr Multiplication::divide(Division& d){
    return nullptr;
}

ExpressionPtr Multiplication::divide(ConstantExpression& ce){
    return nullptr;
}

ExpressionPtr Multiplication::divide(VariableExpression& ve){
    return nullptr;
}

ExpressionPtr Multiplication::mergeMultiplications(Expression& other){
    ExpressionFactory factory;
    vector<ExpressionPtr> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        copiedContent.push_back(move(operands[i]));
    }
    vector<ExpressionPtr> otherOperands = other.getContent();
    for (int j = 0; j < otherOperands.size(); j ++){
        copiedContent.push_back(move(otherOperands[j]));
    }
    //return make_unique<Multiplication>(true, nullptr, nullptr, copiedContent);
    return factory.sign(true).root(nullptr).exponent(nullptr).operands(copiedContent).buildMultiplication().get();
}

ExpressionPtr Multiplication::expandForExponent(){
    if (!exponent){
        return ExpressionPtr (this);
    }else{
        ExpressionPtr expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

ExpressionPtr Multiplication::expandAsExponent(Expression& baseExpression){

    ExpressionFactory factory;

    sanitise();

    ExpressionPtr expanded = factory.buildMultiplication().get();

    // expand the exponents of the innerTerms

    ExpressionPtr copied = this->copy(); // make_unique<Multiplication>(static_cast<Multiplication*> (this->copy()));
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
            
            IntPtr coeffPtr = operands[0]->getValue();

            if (coeffPtr){
                int coeff = *coeffPtr;
                ExpressionPtr newTerm = baseExpression.copy();
                ExpressionPtr newExponent = copied->copy(); // make_unique<Multiplication>(static_cast<Multiplication*> (copied->copy()));
                newExponent->removeExpression(0);
                if (newExponent->getContent().size() == 1){
                    ExpressionPtr singleExponent = move(newExponent->getContent()[0]);
                    ExpressionPtr empty = ExpressionPtr();
                    singleExponent->setParentExpression(empty);
                    newTerm->setExponent(singleExponent);
                }else{
                    newTerm->setExponent(newExponent);
                }
                
                for (int i = 0; i < coeff; i ++){
                    ExpressionPtr ithCopy = newTerm->copy();
                    expanded->appendExpression(*ithCopy);
                }
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

ExpressionPtr Multiplication::expandAsConstNum(Expression& baseExpression, Expression& baseDivision){
    return ExpressionPtr(&baseExpression);
}

ExpressionPtr Multiplication::expandAsNegativeExponent(Expression& baseExpression){
    return ExpressionPtr(&baseExpression);
}

ExpressionPtr Multiplication::factor(){
    return nullptr;
}

vector<ExpressionPtr> Multiplication::getConstantFactors(){
    vector<ExpressionPtr> constantFactors = operands[0]->getConstantFactors();
    return constantFactors;
}

vector<ExpressionPtr> Multiplication::getAllFactors(){
    vector<ExpressionPtr> dummy;
    return dummy;
}

ExpressionPtr Multiplication::copy(){
    ExpressionFactory factory;
    vector<ExpressionPtr> copiedContent;
    for (int i = 0; i < operands.size(); i ++){
        ExpressionPtr ithCopy = move(operands[i]->copy());
        copiedContent.push_back(move(ithCopy));
    }

    if (root != nullptr & exponent != nullptr){        
        return factory.sign(sign).root(root->copy()).exponent(exponent->copy()).operands(copiedContent).buildMultiplication().get(); 
    }else if (root == nullptr & exponent != nullptr){
        return factory.sign(sign).root(nullptr).exponent(exponent->copy()).operands(copiedContent).buildMultiplication().get();
    }else if (root != nullptr & exponent == nullptr){
        return factory.sign(sign).root(root->copy()).exponent(nullptr).operands(copiedContent).buildMultiplication().get();
    }else{
        return factory.sign(sign).root(nullptr).exponent(nullptr).operands(copiedContent).buildMultiplication().get();
    } 
}

string Multiplication::toString(){
    string expressionStr = "";
    for (int i = 0; i < operands.size(); i ++){
        expressionStr += operands[i]->toString();
    }
    if (!sign){
        expressionStr = '-' + expressionStr;
    }
    if (root != nullptr){
        if (!root->isOne()){
            expressionStr = '[' + root->toString() + '|' + expressionStr + ']';
        }
    }
    if (exponent != nullptr){
        if (!exponent->isOne()){
            expressionStr = expressionStr + exponent->exponentToString();
        }
    }
    return expressionStr;
}

string Multiplication::exponentToString(){
    string expressionStr = this->toString();
    if (sign){
        return "^(" + expressionStr + ')';
    }else{
        return '^' + expressionStr;
    }
}
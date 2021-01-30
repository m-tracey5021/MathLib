#include "expression.h"

Constant::Constant(){}

Constant::Constant(bool sign, unique_ptr<Expression> root, unique_ptr<Expression> exponent, int constant): Expression(sign, make_unique<Expression>(root), make_unique<Expression>(exponent)), constant(constant){}

int* Constant::getValue(){
    return &constant;
}

vector<unique_ptr<Expression>> Constant::getContent(){
    vector<unique_ptr<Expression>> content = {unique_ptr<Constant> (this)};
    return content;
}

void Constant::appendExpression(Expression& e){}

void Constant::removeExpression(int i){}

void Constant::replaceExpression(int i, Expression& e){}

void Constant::sanitise(){}

bool Constant::isEqual(Expression& other){return other.isEqual(*this);}

bool Constant::isEqual(Summation& other){return false;}

bool Constant::isEqual(Multiplication& other){return false;}

bool Constant::isEqual(Division& other){return false;}

bool Constant::isEqual(Constant& other){
    if (other.getConstant() == constant){
        return true;
    }else{
        return false;
    }
}

bool Constant::isEqual(Variable& other){return false;}

bool Constant::isAtomic(){
    return true;
}

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

bool Constant::isLikeExpression(Expression& other){
    return false;
}

bool Constant::isMergeable(){
    return true;
}

unique_ptr<Expression> Constant::sum(Summation s){
    unique_ptr<Expression> constantPtr (new Constant(true, nullptr, nullptr, 1));
    return constantPtr;
}

unique_ptr<Expression> Constant::sum(Multiplication m){
    unique_ptr<Expression> constantPtr (new Constant(true, nullptr, nullptr, 1));
    return constantPtr;
}

unique_ptr<Expression> Constant::sum(Division d){
    unique_ptr<Expression> constantPtr (new Constant(true, nullptr, nullptr, 1));
    return constantPtr;
}

unique_ptr<Expression> Constant::sum(Constant c){
    unique_ptr<Expression> constantPtr (new Constant(true, nullptr, nullptr, 1));
    return constantPtr;
}

unique_ptr<Expression> Constant::sum(Variable v){
    unique_ptr<Expression> constantPtr (new Constant(true, nullptr, nullptr, 1));
    return constantPtr;
}

unique_ptr<Expression> Constant::expandForExponent(){
    if (!exponent){
        return unique_ptr<Expression> (this);
    }else{
        unique_ptr<Expression> expanded = exponent->expandAsExponent(*this);
        expanded->sanitise();
        return expanded;
    }
}

unique_ptr<Expression> Constant::expandAsExponent(Expression& baseExpression){
    unique_ptr<Expression> expandedTerm (new Multiplication());

    if (!sign){
        expandedTerm = expandAsNegativeExponent(baseExpression);
        return expandedTerm;
    }else{
        if (constant > 1){
            for (int i = 0; i < constant; i ++){
                unique_ptr<Expression> copiedBase (baseExpression.copy());
                copiedBase->setExponent(nullptr);
                expandedTerm->appendExpression(*copiedBase);
            }
            return expandedTerm;
        }else{
            return unique_ptr<Expression> (this);
        }
    }
}

unique_ptr<Expression> Constant::expandAsConstNum(Expression& baseExpression, Division& baseDivision){

    unique_ptr<Expression> expandedTerm (new Multiplication());
    unique_ptr<Expression> numerator (new Constant(true, nullptr, nullptr, 1));
    unique_ptr<Expression> denominator (baseDivision.getContent()[1]->copy());

    unique_ptr<Expression> newExponent (new Division(true, nullptr, nullptr, move(numerator), move(denominator)));
    unique_ptr<Expression> newTerm (baseExpression.copy());
    newTerm->setExponent(move(newExponent));


    for (int i = 0; i < constant; i ++){
        expandedTerm->appendExpression(*newTerm);
    }

    return expandedTerm;
}

unique_ptr<Expression> Constant::expandAsNegativeExponent(Expression& baseExpression){
    unique_ptr<Expression> expandedTerm (new Multiplication());

    for (int i = 0; i < constant; i ++){
        
        unique_ptr<Expression> newDenom (baseExpression.copy());
        newDenom->setExponent(nullptr);
        
        unique_ptr<Expression> newRational (new Division(true, 
                                                         nullptr, 
                                                         nullptr, 
                                                         unique_ptr<Expression> (new Constant(true, nullptr, nullptr, 1)), 
                                                         move(newDenom)));

        expandedTerm->appendExpression(*newRational);
    }
    return expandedTerm;
}

unique_ptr<Expression> Constant::factor(){
    return unique_ptr<Expression> (this);
}

vector<unique_ptr<Expression>> Constant::getConstantFactors(){
    vector<unique_ptr<Expression>> constantFactors;
    for (int i = 1; i <= constant; i ++){
        if (constant % i == 0){
            constantFactors.push_back(unique_ptr<Expression> (new Constant(true, nullptr, nullptr, i)));
        }
    }
    return constantFactors;
}

vector<unique_ptr<Expression>> Constant::getAllFactors(){

    vector<unique_ptr<Expression>> factors;
    vector<unique_ptr<Expression>> constantFactors = getConstantFactors();

    unique_ptr<Expression> expanded = expandForExponent();
    vector<unique_ptr<Expression>> expandedTerms = expanded->getContent();
    getAllSubTerms(expandedTerms, factors, 0, 0);

    for (unique_ptr<Expression> cf : constantFactors){
        factors.push_back(cf);
    }
    return factors;
}
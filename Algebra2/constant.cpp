#include "expression.h"

Constant::Constant(){}

Constant::Constant(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent, int constant): Expression(sign, make_unique<Expression>(root), make_unique<Expression>(exponent)), constant(constant){}

int* Constant::getValue(){
    return &constant;
}

vector<unique_ptr<Expression>> Constant::getContent(){
    vector<unique_ptr<Expression>> content;
    content.push_back(unique_ptr<Constant>(this));
    return content;
}

void Constant::appendExpression(Expression& e){}

void Constant::removeExpression(int i){}

void Constant::replaceExpression(int i, Expression& e){}

void Constant::sanitise(){}

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
    int i = 9;
    int&& j = 8;
    j = i;
    unique_ptr<Expression> expandedTerm (new Multiplication());
    unique_ptr<Expression> numerator (new Constant(true, nullptr, nullptr, 1));
    unique_ptr<Expression> denominator (baseDivision.getContent()[1]->copy());

    unique_ptr<Expression> newExponent (new Division(true, nullptr, nullptr, move(numerator), move(denominator)));
    unique_ptr<Expression> newTerm (baseExpression.copy());
    newTerm->setExponent(*newExponent);


    for (int i = 0; i < constant; i ++){
        expandedTerm->appendExpression(*newTerm);
    }

    return expandedTerm;
}
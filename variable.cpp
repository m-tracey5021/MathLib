
/*
#include "Algebra/EquationComponents/variable.h"

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
    return this;
}

std::vector<TermBase*> Variable::allFactors(){
    std::vector<TermBase*> dummy;
    return dummy;
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
*/
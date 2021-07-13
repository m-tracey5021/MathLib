#include "equalTo.h"
#include "../symbol.h"
#include "../expressionComponents.h"

EqualToSum::EqualToSum(Symbol& compared): compared(compared){}

void EqualToSum::Visit(SumOp* symbol){
    vector<shared_ptr<Symbol>> children = symbol->getChildren();
    vector<shared_ptr<Symbol>> comparedChildren = compared.getChildren();
    if (comparedChildren.size() != children.size()){
        isEqual = false;
        return;
    }else{
        for (int i = 0; i < children.size(); i ++){
            if (!children[i]->isEqual(comparedChildren[i].get())){
                isEqual = false;
                return;
            }
        }
    }
    isEqual = true;
    
}

void EqualToSum::Visit(MulOp* symbol){
    isEqual = false;
    return;
}

void EqualToSum::Visit(DivOp* symbol){
    isEqual = false;
    return;
}

void EqualToSum::Visit(Exponent* symbol){
    isEqual = false;
    return;     
}

void EqualToSum::Visit(Radical* symbol){
    isEqual = false;
    return;
}

void EqualToSum::Visit(Constant* symbol){
    isEqual = false;
    return;
}

void EqualToSum::Visit(Variable* symbol){
    isEqual = false;
    return;
}

// ============

EqualToMul::EqualToMul(Symbol& compared): compared(compared){}

void EqualToMul::Visit(SumOp* symbol){
    isEqual = false;
    return;
}

void EqualToMul::Visit(MulOp* symbol){
    vector<shared_ptr<Symbol>> children = symbol->getChildren();
    vector<shared_ptr<Symbol>> comparedChildren = compared.getChildren();
    if (comparedChildren.size() != children.size()){
        isEqual = false;
        return;
    }else{
        for (int i = 0; i < children.size(); i ++){
            if (!children[i]->isEqual(comparedChildren[i].get())){
                isEqual = false;
                return;
            }
        }
    }
    isEqual = true;
}

void EqualToMul::Visit(DivOp* symbol){
    isEqual = false;
    return;
}

void EqualToMul::Visit(Exponent* symbol){
    isEqual = false;
    return;     
}

void EqualToMul::Visit(Radical* symbol){
    isEqual = false;
    return;
}

void EqualToMul::Visit(Constant* symbol){
    isEqual = false;
    return;
}

void EqualToMul::Visit(Variable* symbol){
    isEqual = false;
    return;
}

// ============

EqualToDiv::EqualToDiv(Symbol& compared): compared(compared){}

void EqualToDiv::Visit(SumOp* symbol){
    isEqual = false;
    return;
}

void EqualToDiv::Visit(MulOp* symbol){
    isEqual = false;
    return;
}

void EqualToDiv::Visit(DivOp* symbol){
    vector<shared_ptr<Symbol>> children = symbol->getChildren();
    vector<shared_ptr<Symbol>> comparedChildren = compared.getChildren();
    if (comparedChildren.size() != children.size()){
        isEqual = false;
        return;
    }else{
        for (int i = 0; i < children.size(); i ++){
            if (!children[i]->isEqual(comparedChildren[i].get())){
                isEqual = false;
                return;
            }
        }
    }
    isEqual = true;
}

void EqualToDiv::Visit(Exponent* symbol){
    isEqual = false;
    return;     
}

void EqualToDiv::Visit(Radical* symbol){
    isEqual = false;
    return;
}

void EqualToDiv::Visit(Constant* symbol){
    isEqual = false;
    return;
}

void EqualToDiv::Visit(Variable* symbol){
    isEqual = false;
    return;
}

// ============

EqualToExponent::EqualToExponent(Symbol& compared): compared(compared){}

void EqualToExponent::Visit(SumOp* symbol){
    isEqual = false;
    return;
}

void EqualToExponent::Visit(MulOp* symbol){
    isEqual = false;
    return;
}

void EqualToExponent::Visit(DivOp* symbol){
    isEqual = false;
    return;
}

void EqualToExponent::Visit(Exponent* symbol){
    vector<shared_ptr<Symbol>> children = symbol->getChildren();
    vector<shared_ptr<Symbol>> comparedChildren = compared.getChildren();
    if (comparedChildren.size() != children.size()){
        isEqual = false;
        return;
    }else{
        for (int i = 0; i < children.size(); i ++){
            if (!children[i]->isEqual(comparedChildren[i].get())){
                isEqual = false;
                return;
            }
        }
    }
    isEqual = true;  
}

void EqualToExponent::Visit(Radical* symbol){
    isEqual = false;
    return;
}

void EqualToExponent::Visit(Constant* symbol){
    isEqual = false;
    return;
}

void EqualToExponent::Visit(Variable* symbol){
    isEqual = false;
    return;
}

// ============

EqualToRadical::EqualToRadical(Symbol& compared): compared(compared){}

void EqualToRadical::Visit(SumOp* symbol){
    isEqual = false;
    return;
}

void EqualToRadical::Visit(MulOp* symbol){
    isEqual = false;
    return;
}

void EqualToRadical::Visit(DivOp* symbol){
    isEqual = false;
    return;
}

void EqualToRadical::Visit(Exponent* symbol){
    isEqual = false;
    return;     
}

void EqualToRadical::Visit(Radical* symbol){
    vector<shared_ptr<Symbol>> children = symbol->getChildren();
    vector<shared_ptr<Symbol>> comparedChildren = compared.getChildren();
    if (comparedChildren.size() != children.size()){
        isEqual = false;
        return;
    }else{
        for (int i = 0; i < children.size(); i ++){
            if (!children[i]->isEqual(comparedChildren[i].get())){
                isEqual = false;
                return;
            }
        }
    }
    isEqual = true;
}

void EqualToRadical::Visit(Constant* symbol){
    isEqual = false;
    return;
}

void EqualToRadical::Visit(Variable* symbol){
    isEqual = false;
    return;
}

// ============

EqualToConstant::EqualToConstant(Symbol& compared): compared(compared){}

void EqualToConstant::Visit(SumOp* symbol){
    isEqual = false;
    return;
}

void EqualToConstant::Visit(MulOp* symbol){
    isEqual = false;
    return;
}

void EqualToConstant::Visit(DivOp* symbol){
    isEqual = false;
    return;
}

void EqualToConstant::Visit(Exponent* symbol){
    isEqual = false;
    return;     
}

void EqualToConstant::Visit(Radical* symbol){
    isEqual = false;
    return;
}

void EqualToConstant::Visit(Constant* symbol){
    if (compared.getValue() == symbol->getValue()){
        isEqual = true;
    }else{
        isEqual = false;
    }
    
    return;
}

void EqualToConstant::Visit(Variable* symbol){
    isEqual = false;
    return;
}

// ==========


EqualToVariable::EqualToVariable(Symbol& compared): compared(compared){}

void EqualToVariable::Visit(SumOp* symbol){
    isEqual = false;
    return;
}

void EqualToVariable::Visit(MulOp* symbol){
    isEqual = false;
    return;
}

void EqualToVariable::Visit(DivOp* symbol){
    isEqual = false;
    return;
}

void EqualToVariable::Visit(Exponent* symbol){
    isEqual = false;
    return;     
}

void EqualToVariable::Visit(Radical* symbol){
    isEqual = false;
    return;
}

void EqualToVariable::Visit(Constant* symbol){
    isEqual = false;
    return;
}

void EqualToVariable::Visit(Variable* symbol){
    if (compared.getValue() == symbol->getValue()){
        isEqual = true;
    }else{
        isEqual = false;
    }
    
    return;
}
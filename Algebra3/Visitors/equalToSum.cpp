#include "equalToSum.h"
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
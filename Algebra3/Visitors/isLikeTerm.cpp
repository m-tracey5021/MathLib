#include "isLikeTerm.h"
#include "../symbol.h"
#include "../expressionComponents.h"

IsLikeTerm::IsLikeTerm(MulOp& compared): compared(compared){}

void IsLikeTerm::Visit(SumOp* symbol){
    isLikeTerm = false;
}

void IsLikeTerm::Visit(MulOp* symbol){
    shared_ptr<Symbol> coeff = symbol->extractCoeff();
    shared_ptr<Symbol> comparedCoeff = compared.extractCoeff();
    vector<shared_ptr<Symbol>> children = symbol->getChildren();
    vector<shared_ptr<Symbol>> comparedChildren = compared.getChildren();
    if (children.size() != comparedChildren.size()){
        isLikeTerm = false;
        return;
    }else{
        for (int i = 0; i < children.size(); i ++){
            if (!children[i]->isEqual(comparedChildren[i].get())){
                isLikeTerm = false;
                return;
            }
        }
        isLikeTerm = true;
    }
}

void IsLikeTerm::Visit(DivOp* symbol){
    isLikeTerm = false;
}

void IsLikeTerm::Visit(Exponent* symbol){
    isLikeTerm = false;
}

void IsLikeTerm::Visit(Radical* symbol){
    isLikeTerm = false;
}

void IsLikeTerm::Visit(Constant* symbol){
    isLikeTerm = false;
}

void IsLikeTerm::Visit(Variable* symbol){
    isLikeTerm = false;
}

// =============

// MulIsLikeTerm::MulIsLikeTerm(Symbol& compared): compared(compared){}

// void MulIsLikeTerm::Visit(SumOp* symbol){}


// void MulIsLikeTerm::Visit(MulOp* symbol){

// }

// void MulIsLikeTerm::Visit(DivOp* symbol){

// }

// void MulIsLikeTerm::Visit(Exponent* symbol){
  
// }

// void MulIsLikeTerm::Visit(Radical* symbol){

// }

// void MulIsLikeTerm::Visit(Constant* symbol){

// }

// void MulIsLikeTerm::Visit(Variable* symbol){

// }

// // =============

// DivIsLikeTerm::DivIsLikeTerm(Symbol& compared): compared(compared){}

// void DivIsLikeTerm::Visit(SumOp* symbol){}


// void DivIsLikeTerm::Visit(MulOp* symbol){

// }

// void DivIsLikeTerm::Visit(DivOp* symbol){

// }

// void DivIsLikeTerm::Visit(Exponent* symbol){
  
// }

// void DivIsLikeTerm::Visit(Radical* symbol){

// }

// void DivIsLikeTerm::Visit(Constant* symbol){

// }

// void DivIsLikeTerm::Visit(Variable* symbol){

// }

// =============

// SumIsLikeTerm::SumIsLikeTerm(Symbol& compared): compared(compared){}

// void SumIsLikeTerm::Visit(SumOp* symbol){}


// void SumIsLikeTerm::Visit(MulOp* symbol){

// }

// void SumIsLikeTerm::Visit(DivOp* symbol){

// }

// void SumIsLikeTerm::Visit(Exponent* symbol){
  
// }

// void SumIsLikeTerm::Visit(Radical* symbol){

// }

// void SumIsLikeTerm::Visit(Constant* symbol){

// }

// void SumIsLikeTerm::Visit(Variable* symbol){

// }

// // =============

// SumIsLikeTerm::SumIsLikeTerm(Symbol& compared): compared(compared){}

// void SumIsLikeTerm::Visit(SumOp* symbol){}


// void SumIsLikeTerm::Visit(MulOp* symbol){

// }

// void SumIsLikeTerm::Visit(DivOp* symbol){

// }

// void SumIsLikeTerm::Visit(Exponent* symbol){
  
// }

// void SumIsLikeTerm::Visit(Radical* symbol){

// }

// void SumIsLikeTerm::Visit(Constant* symbol){

// }

// void SumIsLikeTerm::Visit(Variable* symbol){

// }

// // =============

// SumIsLikeTerm::SumIsLikeTerm(Symbol& compared): compared(compared){}

// void SumIsLikeTerm::Visit(SumOp* symbol){}


// void SumIsLikeTerm::Visit(MulOp* symbol){

// }

// void SumIsLikeTerm::Visit(DivOp* symbol){

// }

// void SumIsLikeTerm::Visit(Exponent* symbol){
  
// }

// void SumIsLikeTerm::Visit(Radical* symbol){

// }

// void SumIsLikeTerm::Visit(Constant* symbol){

// }

// void SumIsLikeTerm::Visit(Variable* symbol){

// }

// // =============

// SumIsLikeTerm::SumIsLikeTerm(Symbol& compared): compared(compared){}

// void SumIsLikeTerm::Visit(SumOp* symbol){}


// void SumIsLikeTerm::Visit(MulOp* symbol){

// }

// void SumIsLikeTerm::Visit(DivOp* symbol){

// }

// void SumIsLikeTerm::Visit(Exponent* symbol){
  
// }

// void SumIsLikeTerm::Visit(Radical* symbol){

// }

// void SumIsLikeTerm::Visit(Constant* symbol){

// }

// void SumIsLikeTerm::Visit(Variable* symbol){

// }

// // =============

// SumIsLikeTerm::SumIsLikeTerm(Symbol& compared): compared(compared){}

// void SumIsLikeTerm::Visit(SumOp* symbol){}


// void SumIsLikeTerm::Visit(MulOp* symbol){

// }

// void SumIsLikeTerm::Visit(DivOp* symbol){

// }

// void SumIsLikeTerm::Visit(Exponent* symbol){
  
// }

// void SumIsLikeTerm::Visit(Radical* symbol){

// }

// void SumIsLikeTerm::Visit(Constant* symbol){

// }

// void SumIsLikeTerm::Visit(Variable* symbol){

// }

// // =============
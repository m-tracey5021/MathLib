#include "sanitiseMulOp.h"
#include "../symbol.h"
#include "../expressionComponents.h"

SanitiseMulOp::SanitiseMulOp(){}

SanitiseMulOp::~SanitiseMulOp(){}

void SanitiseMulOp::Visit(SumOp* symbol){

}

void SanitiseMulOp::Visit(MulOp* symbol){
    
}

void SanitiseMulOp::Visit(DivOp* symbol){
    
}

void SanitiseMulOp::Visit(Exponent* symbol){
    
}

void SanitiseMulOp::Visit(Radical* symbol){
    
}

void SanitiseMulOp::Visit(Constant* symbol){
    multiplyValue = true;
}

void SanitiseMulOp::Visit(Variable* symbol){

}

void SanitiseMulOp::setOther(shared_ptr<Symbol>& other){
    this->other = other;
}
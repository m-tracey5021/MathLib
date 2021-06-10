#include "appendToMulOp.h"
#include "../symbol.h"
#include "../expressionComponents.h"

AppendToMulOp::AppendToMulOp(Symbol& parent, shared_ptr<Symbol>& child): parent(parent), child(child){}

AppendToMulOp::~AppendToMulOp(){}

void AppendToMulOp::Visit(SumOp* symbol){

}

void AppendToMulOp::Visit(MulOp* symbol){
    appendEach(parent, child);
}

void AppendToMulOp::Visit(DivOp* symbol){
    append(parent, child);
}

void AppendToMulOp::Visit(Exponent* symbol){
    append(parent, child);
}

void AppendToMulOp::Visit(Radical* symbol){
    append(parent, child);
}

void AppendToMulOp::Visit(Constant* symbol){
    append(parent, child);
}

void AppendToMulOp::Visit(Variable* symbol){
    append(parent, child);
}
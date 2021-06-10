#include "appendToSumOp.h"
#include "../symbol.h"
#include "../expressionComponents.h"

AppendToSumOp::AppendToSumOp(Symbol& parent, shared_ptr<Symbol>& child): parent(parent), child(child){}

AppendToSumOp::~AppendToSumOp(){}

void AppendToSumOp::Visit(SumOp* symbol){
    appendEach(parent, child);
}

void AppendToSumOp::Visit(MulOp* symbol){
    append(parent, child);
}

void AppendToSumOp::Visit(DivOp* symbol){
    append(parent, child);
}

void AppendToSumOp::Visit(Exponent* symbol){
    append(parent, child);
}

void AppendToSumOp::Visit(Radical* symbol){
    append(parent, child);
}

void AppendToSumOp::Visit(Constant* symbol){
    append(parent, child);
}

void AppendToSumOp::Visit(Variable* symbol){
    append(parent, child);
}
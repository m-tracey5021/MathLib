#include "add.h"
#include "../symbol.h"
#include "../expressionComponents.h"

AddToSumOp::AddToSumOp(SumOp& lhs): lhs(lhs){}

void AddToSumOp::Visit(SumOp* rhs){

}

void AddToSumOp::Visit(MulOp* rhs){

}

void AddToSumOp::Visit(DivOp* rhs){

}

void AddToSumOp::Visit(Exponent* rhs){
   
}

void AddToSumOp::Visit(Radical* rhs){

}

void AddToSumOp::Visit(Constant* rhs){

}

void AddToSumOp::Visit(Variable* rhs){
    
}

// ========

AddToMulOp::AddToMulOp(MulOp& lhs): lhs(lhs){}

void AddToMulOp::Visit(SumOp* rhs){

}

void AddToMulOp::Visit(MulOp* rhs){

}

void AddToMulOp::Visit(DivOp* rhs){

}

void AddToMulOp::Visit(Exponent* rhs){
   
}

void AddToMulOp::Visit(Radical* rhs){

}

void AddToMulOp::Visit(Constant* rhs){

}

void AddToMulOp::Visit(Variable* rhs){
    
}

// ========

AddToDivOp::AddToDivOp(DivOp& lhs): lhs(lhs){}

void AddToDivOp::Visit(SumOp* rhs){

}

void AddToDivOp::Visit(MulOp* rhs){

}

void AddToDivOp::Visit(DivOp* rhs){

}

void AddToDivOp::Visit(Exponent* rhs){
   
}

void AddToDivOp::Visit(Radical* rhs){

}

void AddToDivOp::Visit(Constant* rhs){

}

void AddToDivOp::Visit(Variable* rhs){
    
}

// ========

AddToExponent::AddToExponent(Exponent& lhs): lhs(lhs){}

void AddToExponent::Visit(SumOp* rhs){

}

void AddToExponent::Visit(MulOp* rhs){

}

void AddToExponent::Visit(DivOp* rhs){

}

void AddToExponent::Visit(Exponent* rhs){
   
}

void AddToExponent::Visit(Radical* rhs){

}

void AddToExponent::Visit(Constant* rhs){

}

void AddToExponent::Visit(Variable* rhs){
    
}

// ========

AddToRadical::AddToRadical(Radical& lhs): lhs(lhs){}

void AddToRadical::Visit(SumOp* rhs){

}

void AddToRadical::Visit(MulOp* rhs){

}

void AddToRadical::Visit(DivOp* rhs){

}

void AddToRadical::Visit(Exponent* rhs){
   
}

void AddToRadical::Visit(Radical* rhs){

}

void AddToRadical::Visit(Constant* rhs){

}

void AddToRadical::Visit(Variable* rhs){
    
}

// ========

AddToConstant::AddToConstant(Constant& lhs): lhs(lhs){}

void AddToConstant::Visit(SumOp* rhs){

}

void AddToConstant::Visit(MulOp* rhs){

}

void AddToConstant::Visit(DivOp* rhs){

}

void AddToConstant::Visit(Exponent* rhs){
   
}

void AddToConstant::Visit(Radical* rhs){

}

void AddToConstant::Visit(Constant* rhs){
    int total = *lhs.getValue() + *rhs->getValue();
    bool sign = true;
    if (total < 0){
        sign = false;
        total = total + (2 * (-1 * total));
    }
    shared_ptr<Symbol> added = make_shared<Constant>(sign, total);
    result = added;
}

void AddToConstant::Visit(Variable* rhs){
    shared_ptr<Symbol> added = make_shared<SumOp>(true);
    shared_ptr<Symbol> lhsWrapped = lhs.getWrapped();
    shared_ptr<Symbol> rhsWrapped = rhs->getWrapped();
    added->appendChild(lhsWrapped);
    added->appendChild(rhsWrapped);
    result = added;
}

// ========

AddToVariable::AddToVariable(Variable& lhs): lhs(lhs){}

void AddToVariable::Visit(SumOp* rhs){

}

void AddToVariable::Visit(MulOp* rhs){

}

void AddToVariable::Visit(DivOp* rhs){

}

void AddToVariable::Visit(Exponent* rhs){
   
}

void AddToVariable::Visit(Radical* rhs){

}

void AddToVariable::Visit(Constant* rhs){
    shared_ptr<Symbol> added = make_shared<SumOp>(true);
    shared_ptr<Symbol> lhsWrapped = lhs.getWrapped();
    shared_ptr<Symbol> rhsWrapped = rhs->getWrapped();
    added->appendChild(lhsWrapped);
    added->appendChild(rhsWrapped);
    result = added;
}

void AddToVariable::Visit(Variable* rhs){
    
}

// ========
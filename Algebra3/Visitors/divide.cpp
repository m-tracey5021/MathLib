#include "divide.h"
#include "../symbol.h"
#include "../expressionComponents.h"

DivideSumOp::DivideSumOp(SumOp& lhs): lhs(lhs){}

void DivideSumOp::Visit(SumOp* rhs){

}

void DivideSumOp::Visit(MulOp* rhs){

}

void DivideSumOp::Visit(DivOp* rhs){

}

void DivideSumOp::Visit(Exponent* rhs){
   
}

void DivideSumOp::Visit(Radical* rhs){

}

void DivideSumOp::Visit(Constant* rhs){

}

void DivideSumOp::Visit(Variable* rhs){
    
}

// ========

DivideMulOp::DivideMulOp(MulOp& lhs): lhs(lhs){}

void DivideMulOp::Visit(SumOp* rhs){

}

void DivideMulOp::Visit(MulOp* rhs){

}

void DivideMulOp::Visit(DivOp* rhs){

}

void DivideMulOp::Visit(Exponent* rhs){
   
}

void DivideMulOp::Visit(Radical* rhs){

}

void DivideMulOp::Visit(Constant* rhs){

}

void DivideMulOp::Visit(Variable* rhs){
    
}

// ========

DivideDivOp::DivideDivOp(DivOp& lhs): lhs(lhs){}

void DivideDivOp::Visit(SumOp* rhs){

}

void DivideDivOp::Visit(MulOp* rhs){

}

void DivideDivOp::Visit(DivOp* rhs){

}

void DivideDivOp::Visit(Exponent* rhs){
   
}

void DivideDivOp::Visit(Radical* rhs){

}

void DivideDivOp::Visit(Constant* rhs){

}

void DivideDivOp::Visit(Variable* rhs){
    
}

// ========

DivideExponent::DivideExponent(Exponent& lhs): lhs(lhs){}

void DivideExponent::Visit(SumOp* rhs){

}

void DivideExponent::Visit(MulOp* rhs){

}

void DivideExponent::Visit(DivOp* rhs){

}

void DivideExponent::Visit(Exponent* rhs){
   
}

void DivideExponent::Visit(Radical* rhs){

}

void DivideExponent::Visit(Constant* rhs){

}

void DivideExponent::Visit(Variable* rhs){
    
}

// ========

DivideRadical::DivideRadical(Radical& lhs): lhs(lhs){}

void DivideRadical::Visit(SumOp* rhs){

}

void DivideRadical::Visit(MulOp* rhs){

}

void DivideRadical::Visit(DivOp* rhs){

}

void DivideRadical::Visit(Exponent* rhs){
   
}

void DivideRadical::Visit(Radical* rhs){

}

void DivideRadical::Visit(Constant* rhs){

}

void DivideRadical::Visit(Variable* rhs){
    
}

// ========

DivideConstant::DivideConstant(Constant& lhs): lhs(lhs){}

void DivideConstant::Visit(SumOp* rhs){

}

void DivideConstant::Visit(MulOp* rhs){

}

void DivideConstant::Visit(DivOp* rhs){

}

void DivideConstant::Visit(Exponent* rhs){
   
}

void DivideConstant::Visit(Radical* rhs){

}

void DivideConstant::Visit(Constant* rhs){
    int total = *lhs.getValue() / *rhs->getValue();
    bool sign;
    if (lhs.getSign() == rhs->getSign()){
        sign = true;
    }else{
        sign = false;
    }
    shared_ptr<Symbol> divided = make_shared<Constant>(sign, total);
    result = divided;
}

void DivideConstant::Visit(Variable* rhs){

}

// ========

DivideVariable::DivideVariable(Variable& lhs): lhs(lhs){}

void DivideVariable::Visit(SumOp* rhs){

}

void DivideVariable::Visit(MulOp* rhs){

}

void DivideVariable::Visit(DivOp* rhs){

}

void DivideVariable::Visit(Exponent* rhs){
   
}

void DivideVariable::Visit(Radical* rhs){

}

void DivideVariable::Visit(Constant* rhs){
    shared_ptr<Symbol> added = make_shared<SumOp>(true);
    shared_ptr<Symbol> lhsWrapped = lhs.getWrapped();
    shared_ptr<Symbol> rhsWrapped = rhs->getWrapped();
    added->appendChild(lhsWrapped);
    added->appendChild(rhsWrapped);
    result = added;
}

void DivideVariable::Visit(Variable* rhs){
    
}

// ========
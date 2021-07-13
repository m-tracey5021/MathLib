#include "multiply.h"
#include "../symbol.h"
#include "../expressionComponents.h"

shared_ptr<Symbol> distributeForEach(vector<shared_ptr<Symbol>>& lhs, vector<shared_ptr<Symbol>>& rhs){
    shared_ptr<Symbol> result = make_shared<SumOp>();
    for (int i = 0; i < lhs.size(); i ++){
        for (int j = 0; j < rhs.size(); j ++){
            shared_ptr<Symbol> multiplication = make_shared<MulOp>();
            shared_ptr<Symbol> first = lhs[i]->copy();
            shared_ptr<Symbol> second = rhs[j]->copy();
            multiplication->appendChild(first);
            multiplication->appendChild(second);
            result->appendChild(multiplication);
        }
    }
    return result;
}

shared_ptr<Symbol> distributeForSingle(vector<shared_ptr<Symbol>>& sum, Symbol* single){
    shared_ptr<Symbol> result = make_shared<SumOp>();
    for (int i = 0; i < sum.size(); i ++){
        shared_ptr<Symbol> multiplication = make_shared<MulOp>();
        shared_ptr<Symbol> first = sum[i]->copy();
        shared_ptr<Symbol> second = single->copy();
        multiplication->appendChild(first);
        multiplication->appendChild(second);
        result->appendChild(multiplication);
    }
    return result;
}

shared_ptr<Symbol> multiply(Symbol& lhs, Symbol* rhs){
    shared_ptr<Symbol> multiplication = make_shared<MulOp>();
    shared_ptr<Symbol> first = lhs.copy();
    shared_ptr<Symbol> second = rhs->copy();
    multiplication->appendChild(first);
    multiplication->appendChild(second);
    return multiplication;
}

shared_ptr<Symbol> appendToMulOp(Symbol& lhs, Symbol* rhs){
    shared_ptr<Symbol> result = lhs.copy();
    shared_ptr<Symbol> appended = rhs->copy();
    result->appendChild(appended);
    return result;
}

// shared_ptr<Symbol> appendMulOpToMulOp(Symbol& lhs, Symbol* rhs){
//     shared_ptr<Symbol> result = lhs.copy();
//     for (int i = 0; i < rhs->getChildren().size(); i ++){
//         shared_ptr<Symbol> appended = rhs->getChildren()[i]->copy();
//         result->appendChild(appended);
//     }
//     return result;
// }

MultiplySumOp::MultiplySumOp(SumOp& lhs): lhs(lhs){}

void MultiplySumOp::Visit(SumOp* rhs){
    vector<shared_ptr<Symbol>> lhsChildren = lhs.getChildren();
    vector<shared_ptr<Symbol>> rhsChildren = rhs->getChildren();
    result = distributeForEach(lhsChildren, rhsChildren);
}

void MultiplySumOp::Visit(MulOp* rhs){
    vector<shared_ptr<Symbol>> lhsChildren = lhs.getChildren();
    result = distributeForSingle(lhsChildren, rhs);
}

void MultiplySumOp::Visit(DivOp* rhs){
    vector<shared_ptr<Symbol>> lhsChildren = lhs.getChildren();
    result = distributeForSingle(lhsChildren, rhs);
}

void MultiplySumOp::Visit(Exponent* rhs){
    vector<shared_ptr<Symbol>> lhsChildren = lhs.getChildren();
    result = distributeForSingle(lhsChildren, rhs);
}

void MultiplySumOp::Visit(Radical* rhs){
    vector<shared_ptr<Symbol>> lhsChildren = lhs.getChildren();
    result = distributeForSingle(lhsChildren, rhs);
}

void MultiplySumOp::Visit(Constant* rhs){
    vector<shared_ptr<Symbol>> lhsChildren = lhs.getChildren();
    result = distributeForSingle(lhsChildren, rhs);
}

void MultiplySumOp::Visit(Variable* rhs){
    vector<shared_ptr<Symbol>> lhsChildren = lhs.getChildren();
    result = distributeForSingle(lhsChildren, rhs);
}

// ========

MultiplyMulOp::MultiplyMulOp(MulOp& lhs): lhs(lhs){}

void MultiplyMulOp::Visit(SumOp* rhs){
    vector<shared_ptr<Symbol>> rhsChildren = rhs->getChildren();
    result = distributeForSingle(rhsChildren, &lhs);
}

void MultiplyMulOp::Visit(MulOp* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyMulOp::Visit(DivOp* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyMulOp::Visit(Exponent* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyMulOp::Visit(Radical* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyMulOp::Visit(Constant* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyMulOp::Visit(Variable* rhs){
    result = appendToMulOp(lhs, rhs);
}

// ========

MultiplyDivOp::MultiplyDivOp(DivOp& lhs): lhs(lhs){}

void MultiplyDivOp::Visit(SumOp* rhs){
    vector<shared_ptr<Symbol>> rhsChildren = rhs->getChildren();
    result = distributeForSingle(rhsChildren, &lhs);
}

void MultiplyDivOp::Visit(MulOp* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyDivOp::Visit(DivOp* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyDivOp::Visit(Exponent* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyDivOp::Visit(Radical* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyDivOp::Visit(Constant* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyDivOp::Visit(Variable* rhs){
    result = multiply(lhs, rhs);
}

// ========

MultiplyExponent::MultiplyExponent(Exponent& lhs): lhs(lhs){}

void MultiplyExponent::Visit(SumOp* rhs){
    vector<shared_ptr<Symbol>> rhsChildren = rhs->getChildren();
    result = distributeForSingle(rhsChildren, &lhs);
}

void MultiplyExponent::Visit(MulOp* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyExponent::Visit(DivOp* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyExponent::Visit(Exponent* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyExponent::Visit(Radical* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyExponent::Visit(Constant* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyExponent::Visit(Variable* rhs){
    result = multiply(lhs, rhs);
}

// ========

MultiplyRadical::MultiplyRadical(Radical& lhs): lhs(lhs){}

void MultiplyRadical::Visit(SumOp* rhs){
    vector<shared_ptr<Symbol>> rhsChildren = rhs->getChildren();
    result = distributeForSingle(rhsChildren, &lhs);
}

void MultiplyRadical::Visit(MulOp* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyRadical::Visit(DivOp* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyRadical::Visit(Exponent* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyRadical::Visit(Radical* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyRadical::Visit(Constant* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyRadical::Visit(Variable* rhs){
    result = multiply(lhs, rhs);
}

// ========

MultiplyConstant::MultiplyConstant(Constant& lhs): lhs(lhs){}

void MultiplyConstant::Visit(SumOp* rhs){
    vector<shared_ptr<Symbol>> rhsChildren = rhs->getChildren();
    result = distributeForSingle(rhsChildren, &lhs);
}

void MultiplyConstant::Visit(MulOp* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyConstant::Visit(DivOp* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyConstant::Visit(Exponent* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyConstant::Visit(Radical* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyConstant::Visit(Constant* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyConstant::Visit(Variable* rhs){
    result = multiply(lhs, rhs);
}

// ========

MultiplyVariable::MultiplyVariable(Variable& lhs): lhs(lhs){}

void MultiplyVariable::Visit(SumOp* rhs){
    vector<shared_ptr<Symbol>> rhsChildren = rhs->getChildren();
    result = distributeForSingle(rhsChildren, &lhs);
}

void MultiplyVariable::Visit(MulOp* rhs){
    result = appendToMulOp(lhs, rhs);
}

void MultiplyVariable::Visit(DivOp* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyVariable::Visit(Exponent* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyVariable::Visit(Radical* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyVariable::Visit(Constant* rhs){
    result = multiply(lhs, rhs);
}

void MultiplyVariable::Visit(Variable* rhs){
    result = multiply(lhs, rhs);
}

// ========
#include "append.h"
#include "../symbol.h"
#include "../expressionComponents.h"

void append(Symbol& parent, shared_ptr<Symbol>& child){
    vector<int> parentPath = parent.getPath();
    shared_ptr<Symbol> parentWrapped = parent.getWrapped();
    shared_ptr<Expression> parentExpression = parent.getParentExpression();
    
    parentPath.push_back(parent.getChildren().size());
    child->setPath(parentPath);
    child->setParent(parentWrapped);
    child->setParentExpression(parentExpression);
    parent.appendChild(child);
}

void appendEach(Symbol& parent, shared_ptr<Symbol>& child){
    vector<int> path = parent.getPath();
    shared_ptr<Symbol> parentWrapped = parent.getWrapped();
    shared_ptr<Expression> parentExpression = parent.getParentExpression();

    vector<shared_ptr<Symbol>> children = child->getChildren();
    for (int i = 0; i < children.size(); i ++){
        path.push_back(parent.getChildren().size());
        children[i]->setParent(parentWrapped);
        children[i]->setParentExpression(parentExpression);
        parent.appendChild(children[i]);

        path.erase(path.end());
    }
}

AppendToSumOp::AppendToSumOp(SumOp& parent): parent(parent){}

void AppendToSumOp::Visit(SumOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    appendEach(parent, wrappedChild);
}

void AppendToSumOp::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToSumOp::Visit(DivOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToSumOp::Visit(Exponent* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToSumOp::Visit(Radical* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToSumOp::Visit(Constant* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToSumOp::Visit(Variable* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

// ========

AppendToMulOp::AppendToMulOp(MulOp& parent): parent(parent){}

void AppendToMulOp::Visit(SumOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToMulOp::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    appendEach(parent, wrappedChild);
}

void AppendToMulOp::Visit(DivOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToMulOp::Visit(Exponent* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToMulOp::Visit(Radical* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToMulOp::Visit(Constant* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToMulOp::Visit(Variable* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

// ========

AppendToDivOp::AppendToDivOp(DivOp& parent): parent(parent){}

void AppendToDivOp::Visit(SumOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToDivOp::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToDivOp::Visit(DivOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToDivOp::Visit(Exponent* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToDivOp::Visit(Radical* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToDivOp::Visit(Constant* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToDivOp::Visit(Variable* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

// ========

AppendToExponent::AppendToExponent(Exponent& parent): parent(parent){}

void AppendToExponent::Visit(SumOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToExponent::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToExponent::Visit(DivOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToExponent::Visit(Exponent* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToExponent::Visit(Radical* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToExponent::Visit(Constant* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToExponent::Visit(Variable* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

// ========

AppendToRadical::AppendToRadical(Radical& parent): parent(parent){}

void AppendToRadical::Visit(SumOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToRadical::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToRadical::Visit(DivOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToRadical::Visit(Exponent* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToRadical::Visit(Radical* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToRadical::Visit(Constant* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToRadical::Visit(Variable* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

// ========

AppendToConstant::AppendToConstant(Constant& parent): parent(parent){}

void AppendToConstant::Visit(SumOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToConstant::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToConstant::Visit(DivOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToConstant::Visit(Exponent* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToConstant::Visit(Radical* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToConstant::Visit(Constant* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToConstant::Visit(Variable* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

// ========

AppendToVariable::AppendToVariable(Variable& parent): parent(parent){}

void AppendToVariable::Visit(SumOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToVariable::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToVariable::Visit(DivOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToVariable::Visit(Exponent* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToVariable::Visit(Radical* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToVariable::Visit(Constant* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

void AppendToVariable::Visit(Variable* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(parent, wrappedChild);
}

// ========

// decides what to do with the parent

Append::Append(shared_ptr<Symbol> child): child(child){}

Append::~Append(){}

void Append::Visit(SumOp* parent){
    shared_ptr<AppendToSumOp> append = make_shared<AppendToSumOp>(*parent);
    child->accept(append.get());
}

void Append::Visit(MulOp* parent){
    shared_ptr<AppendToMulOp> append = make_shared<AppendToMulOp>(*parent);
    child->accept(append.get());
}

void Append::Visit(DivOp* parent){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(*parent, wrappedChild);
}

void Append::Visit(Exponent* parent){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(*parent, wrappedChild);
}

void Append::Visit(Radical* parent){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(*parent, wrappedChild);
}

void Append::Visit(Constant* parent){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(*parent, wrappedChild);
}

void Append::Visit(Variable* parent){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    append(*parent, wrappedChild);
}
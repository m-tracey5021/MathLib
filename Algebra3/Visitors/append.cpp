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

}

void AppendToSumOp::Visit(DivOp* child){

}

void AppendToSumOp::Visit(Exponent* child){
   
}

void AppendToSumOp::Visit(Radical* child){

}

void AppendToSumOp::Visit(Constant* child){

}

void AppendToSumOp::Visit(Variable* child){
    
}

// ========

AppendToMulOp::AppendToMulOp(MulOp& parent): parent(parent){}

void AppendToMulOp::Visit(SumOp* child){

}

void AppendToMulOp::Visit(MulOp* child){
    shared_ptr<Symbol> wrappedChild = child->getWrapped();
    appendEach(parent, wrappedChild);
}

void AppendToMulOp::Visit(DivOp* child){

}

void AppendToMulOp::Visit(Exponent* child){
   
}

void AppendToMulOp::Visit(Radical* child){

}

void AppendToMulOp::Visit(Constant* child){

}

void AppendToMulOp::Visit(Variable* child){
    
}

// ========

AppendToDivOp::AppendToDivOp(DivOp& parent): parent(parent){}

void AppendToDivOp::Visit(SumOp* child){

}

void AppendToDivOp::Visit(MulOp* child){

}

void AppendToDivOp::Visit(DivOp* child){

}

void AppendToDivOp::Visit(Exponent* child){
   
}

void AppendToDivOp::Visit(Radical* child){

}

void AppendToDivOp::Visit(Constant* child){

}

void AppendToDivOp::Visit(Variable* child){
    
}

// ========

AppendToExponent::AppendToExponent(Exponent& parent): parent(parent){}

void AppendToExponent::Visit(SumOp* child){

}

void AppendToExponent::Visit(MulOp* child){

}

void AppendToExponent::Visit(DivOp* child){

}

void AppendToExponent::Visit(Exponent* child){
   
}

void AppendToExponent::Visit(Radical* child){

}

void AppendToExponent::Visit(Constant* child){

}

void AppendToExponent::Visit(Variable* child){
    
}

// ========

AppendToRadical::AppendToRadical(Radical& parent): parent(parent){}

void AppendToRadical::Visit(SumOp* child){

}

void AppendToRadical::Visit(MulOp* child){

}

void AppendToRadical::Visit(DivOp* child){

}

void AppendToRadical::Visit(Exponent* child){
   
}

void AppendToRadical::Visit(Radical* child){

}

void AppendToRadical::Visit(Constant* child){

}

void AppendToRadical::Visit(Variable* child){
    
}

// ========

AppendToConstant::AppendToConstant(Constant& parent): parent(parent){}

void AppendToConstant::Visit(SumOp* child){

}

void AppendToConstant::Visit(MulOp* child){

}

void AppendToConstant::Visit(DivOp* child){

}

void AppendToConstant::Visit(Exponent* child){
   
}

void AppendToConstant::Visit(Radical* child){

}

void AppendToConstant::Visit(Constant* child){

}

void AppendToConstant::Visit(Variable* child){

}

// ========

AppendToVariable::AppendToVariable(Variable& parent): parent(parent){}

void AppendToVariable::Visit(SumOp* child){

}

void AppendToVariable::Visit(MulOp* child){

}

void AppendToVariable::Visit(DivOp* child){

}

void AppendToVariable::Visit(Exponent* child){
   
}

void AppendToVariable::Visit(Radical* child){

}

void AppendToVariable::Visit(Constant* child){

}

void AppendToVariable::Visit(Variable* child){
    
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
    append(*child, child);
}

void Append::Visit(Exponent* parent){
    append(*child, child);
}

void Append::Visit(Radical* parent){
    append(*child, child);
}

void Append::Visit(Constant* parent){
    append(*child, child);
}

void Append::Visit(Variable* parent){
    append(*child, child);
}
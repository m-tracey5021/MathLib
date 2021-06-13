#include "append.h"
#include "appendToSumOp.h"
#include "appendToMulOp.h"
#include "../symbol.h"
#include "../expressionComponents.h"

// decides what to do with the parent

Append::Append(shared_ptr<Symbol> child): child(child){}

Append::~Append(){}

void Append::Visit(SumOp* symbol){
    shared_ptr<AppendToSumOp> append = make_shared<AppendToSumOp>(*symbol, child);
    child->accept(append.get());
}

void Append::Visit(MulOp* symbol){
    shared_ptr<AppendToMulOp> append = make_shared<AppendToMulOp>(*symbol, child);
    child->accept(append.get());
}

void Append::Visit(DivOp* symbol){
    append(*symbol, child);
}

void Append::Visit(Exponent* symbol){
    append(*symbol, child);
}

void Append::Visit(Radical* symbol){
    append(*symbol, child);
}

void Append::Visit(Constant* symbol){
    append(*symbol, child);
}

void Append::Visit(Variable* symbol){
    append(*symbol, child);
}

void append(Symbol& parent, shared_ptr<Symbol>& child){
    vector<int> parentPath = parent.getPath();
    shared_ptr<Symbol> parentWrapped = parent.getWrapped();
    shared_ptr<Expression> parentExpression = parent.getParentExpression();
    

    parentPath.push_back(parent.getChildren().size());
    // child->setIndex(parent.getChildren().size());
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
        // children[i]->setIndex(i);
        children[i]->setParent(parentWrapped);
        children[i]->setParentExpression(parentExpression);
        parent.appendChild(children[i]);

        path.erase(path.end());
    }
}
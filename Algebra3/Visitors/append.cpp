#include "append.h"
#include "../symbol.h"

Append::Append(){}

void Append::append(Symbol& parent, shared_ptr<Symbol>& child){
    child->setIndex(parent.getChildren().size());
    child->setParentExpression(parent.getParentExpression());
    parent.getChildren().push_back(move(child));
}

void Append::appendEach(Symbol& parent, shared_ptr<Symbol>& child){
    vector<shared_ptr<Symbol>>& children = child->getChildren();
    for (int i = 0; i < children.size(); i ++){
        children[i]->setIndex(i);
        children[i]->setParentExpression(parent.getParentExpression());
        parent.getChildren().push_back(move(children[i]));
    }
}
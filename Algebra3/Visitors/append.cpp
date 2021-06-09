#include "append.h"
#include "../symbol.h"

Append::Append(){}

void Append::append(Symbol& parent, shared_ptr<Symbol>& child){
    child->setIndex(parent.getChildren().size());
    child->setParentExpression(parent.getParentExpression());
    parent.getChildren().push_back(move(child));
}
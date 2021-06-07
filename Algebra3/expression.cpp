#include "expression.h"

Expression::Expression(){}

Expression::Expression(unique_ptr<Symbol>& root): root(move(root)){} 

unique_ptr<Symbol>& Expression::getRoot(){return root;}

unique_ptr<Symbol>& Expression::getRootNull(){return rootNull;}

unique_ptr<Symbol>& Expression::getNode(Symbol* target){
    
}

unique_ptr<Symbol>& Expression::getParent(Symbol* target){
    return getParent(target, rootNull, root);
}

unique_ptr<Symbol>& Expression::getParent(Symbol* target, unique_ptr<Symbol>& parent, unique_ptr<Symbol>& child){
    if (child.get() == target){
        return parent;
    }else{
        vector<unique_ptr<Symbol>>& grandchildren = child->getChildren();
        for (int i = 0; i < grandchildren.size(); i ++){
            unique_ptr<Symbol>& result = getParent(target, child, grandchildren[i]);
            if (result.get() != nullptr){
                return result;
            }
        }
        return rootNull;
    }
}

void Expression::setRoot(unique_ptr<Symbol>& root){
    this->root = move(root);
}

void Expression::replaceNode(Symbol* target, unique_ptr<Symbol>& symbol){
    unique_ptr<Symbol>& parent = target->getParent();
    vector<unique_ptr<Symbol>>& children = target->getChildren();
    if (parent.get() != nullptr){
        parent->replaceChild(symbol, target->getIndex());
    }else{
        root = move(symbol);
    }
    
    target->setIndex(-1);
}

void Expression::expandExponents(){
    root->expandExponent(nullptr);
}

string Expression::toString(){
    return root->toString(false);
}

string Expression::toString(int offset){
    return root->toString(1, offset);
}

void link(shared_ptr<Expression>& expression, unique_ptr<Symbol>& root){
    root->setParentExpression(expression);
    expression->setRoot(root);

}


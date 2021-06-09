#include "expression.h"

Expression::Expression(){}

Expression::Expression(shared_ptr<Symbol>& root): root(move(root)){} 

shared_ptr<Symbol>& Expression::getRoot(){return root;}

unique_ptr<Symbol>& Expression::getRootNull(){return rootNull;}

shared_ptr<Symbol>& Expression::getNode(Symbol* target){
    
}

// shared_ptr<Symbol>& Expression::getParent(Symbol* target){
//     return getParent(target, rootNull, root);
// }

// shared_ptr<Symbol>& Expression::getParent(Symbol* target, shared_ptr<Symbol>& parent, shared_ptr<Symbol>& child){
//     if (child.get() == target){
//         return parent;
//     }else{
//         vector<shared_ptr<Symbol>>& grandchildren = child->getChildren();
//         for (int i = 0; i < grandchildren.size(); i ++){
//             shared_ptr<Symbol>& result = getParent(target, child, grandchildren[i]);
//             if (result.get() != nullptr){
//                 return result;
//             }
//         }
//         return rootNull;
//     }
// }

void Expression::setRoot(shared_ptr<Symbol>& root){
    this->root = move(root);
}

void Expression::replaceNode(Symbol* target, shared_ptr<Symbol>& symbol){
    shared_ptr<Symbol>& parent = target->getParent();
    vector<shared_ptr<Symbol>>& children = target->getChildren();
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

void link(shared_ptr<Expression>& expression, shared_ptr<Symbol>& root){
    root->setParentExpression(expression);
    expression->setRoot(root);

}


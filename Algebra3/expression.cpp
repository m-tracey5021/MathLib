#include "expression.h"
#include "Visitors/append.h"

Expression::Expression(){}

Expression::Expression(shared_ptr<Symbol>& root): root(move(root)){
    vector<int> emptyPath;
    root->setPath(emptyPath);
} 

shared_ptr<Symbol>& Expression::getRoot(){return root;}

shared_ptr<Symbol>& Expression::getRootNull(){return rootNull;}

shared_ptr<Symbol> Expression::getNode(vector<int> path){
    if (path.size() == 0){
        return root;
    }else{
        shared_ptr<Symbol> current = root;
        for (int index : path){
            vector<shared_ptr<Symbol>> children = current->getChildren();
            if (children.size() < index){
                return current;
            }else{
                current = current->getChildren()[index];
            }
        }
        return current;
    }
    
}

shared_ptr<Symbol> Expression::getNode(Symbol* target){
    optional<shared_ptr<Symbol>> node = getNode(target, root);
    if (node){
        return *node;
    }else{
        return rootNull;
    }
}

optional<shared_ptr<Symbol>> Expression::getNode(Symbol* target, shared_ptr<Symbol> current){
    optional<shared_ptr<Symbol>> node;
    if (current.get() == target){
        node.emplace(current);
        return node;
    }else{
        vector<shared_ptr<Symbol>> children = current->getChildren();
        for (int i = 0; i < children.size(); i ++){
            optional<shared_ptr<Symbol>> result = getNode(target, children[i]);
            if (result){
                return result;
            }
        }
        node = nullopt;
        return node;
    }
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
    this->root = root;
    vector<int> emptyPath;
    root->setPath(emptyPath);
}

void Expression::appendNode(shared_ptr<Symbol>& parent, shared_ptr<Symbol>& child){
    shared_ptr<Append> append = make_shared<Append>(child);
    parent->accept(append.get());

}

void Expression::removeNode(Symbol* target){
    vector<int> path = target->getPath();
    shared_ptr<Symbol> parent = target->getParent();
    vector<shared_ptr<Symbol>>& siblings = parent->getChildren();
    siblings.erase(siblings.begin() + path[path.size() - 1]);
    for (int i = path[path.size() - 1]; i < siblings.size(); i ++){
        siblings[i]->setPathValue(i);
    }
    vector<int> emptyPath;
    target->setPath(emptyPath);
}

void Expression::insertNode(Symbol* target, shared_ptr<Symbol>& replacement){
    vector<int> path = target->getPath();
    shared_ptr<Symbol> parent = target->getParent();
    vector<shared_ptr<Symbol>> targetChildren = target->getChildren();
    replacement->setChildren(targetChildren);
    if (parent.get() == nullptr){
        setRoot(replacement);
    }else{
        vector<shared_ptr<Symbol>>& siblings = parent->getChildren();
        siblings.erase(siblings.begin() + path[path.size() - 1]);
        siblings.insert(siblings.begin() + path[path.size() - 1], replacement); 
        replacement->setPath(path);
        replacement->setParent(parent);
        vector<int> emptyPath;   
        target->setPath(emptyPath);
    }
}

void Expression::replaceNode(Symbol* target, shared_ptr<Symbol>& replacement){
    vector<int> path = target->getPath();
    shared_ptr<Symbol> parent = target->getParent();
    if (parent.get() == nullptr){
        setRoot(replacement);
    }else{
        vector<shared_ptr<Symbol>>& siblings = parent->getChildren();
        siblings.erase(siblings.begin() + path[path.size() - 1]);
        siblings.insert(siblings.begin() + path[path.size() - 1], replacement);    
        replacement->setPath(path);  
        replacement->setParent(parent);
        vector<int> emptyPath;   
        target->setPath(emptyPath);
    }
    
}

void Expression::evaluateConstants(){
    root->evaluateConstants();
}

void Expression::expandExponents(){
    root->expandExponent(nullptr);
}

void Expression::sumLikeTerms(){
    root->sumLikeTerms();
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


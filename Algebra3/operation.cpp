#include "operation.h"
#include "expressionComponents.h"

Operation::Operation(): Symbol(){}

Operation::Operation(char op): Symbol(op){}

Operation::Operation(char op, bool sign): Symbol(op, sign){}

Operation::Operation(char op, bool sign, vector<unique_ptr<Symbol>>& children): Symbol(op, sign, children){}

Operation::Operation(char op, bool sign, shared_ptr<Expression>& parentExpression): Symbol(op, sign, parentExpression){}

Operation::Operation(char op, bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Symbol(op, sign, children, parentExpression){}

Operation::~Operation() = default;

// Operation::Operation(char op, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, auxOp), operands(move(operands)){}

// Operation::Operation(char op, bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, sign, auxOp), operands(move(operands)){}



int Operation::getValue(){return 0;}

bool Operation::isAtomic(){return false;}

bool Operation::isAtomicExponent(){return false;}

bool Operation::isAtomicNumerator(){return false;}

void Operation::setChildren(vector<unique_ptr<Symbol>>& children){
    this->children = move(children);
}

void Operation::appendChild(unique_ptr<Symbol>& child){
    child->setIndex(children.size());
    child->setParentExpression(parentExpression);
    children.push_back(move(child));
    return;
}

void Operation::appendChildren(vector<unique_ptr<Symbol>>& children){
    int currentSize = children.size();
    for (int i = 0; i < children.size(); i ++){
        children[i]->setIndex(children.size() + i);
        children[i]->setParentExpression(parentExpression);
        children.push_back(move(children[i]));
    }
    return;
}

void Operation::appendChildren(vector<unique_ptr<Symbol>>& children, int n){
    
    for (unique_ptr<Symbol>& child : children){
        child->setIndex(n);
        child->setParentExpression(parentExpression);
        children.insert(children.begin() + n, move(child));
        n ++;
    }
    for (int i = n; i < children.size(); i ++){
        children[i]->setIndex(i);
    }
    return;
}

void Operation::replaceChild(unique_ptr<Symbol>& child, int n){
    for (int i = 0; i < children.size(); i ++){
        if (i == n){
            child->setIndex(n);
            child->setParentExpression(parentExpression);
            children[i] = move(child);
            
        }
    }
    return;
}

void Operation::replaceChild(unique_ptr<SumOp>& child, int n){
    for (int i = 0; i < children.size(); i ++){
        if (i == n){
            child->setIndex(n);
            child->setParentExpression(parentExpression);
            children[i] = move(child);
            
        }
    }
    return;
}

void Operation::replaceChild(unique_ptr<MulOp>& child, int n){
    for (int i = 0; i < children.size(); i ++){
        if (i == n){
            child->setIndex(n);
            child->setParentExpression(parentExpression);
            children[i] = move(child);
            
        }
    }
    return;
}

void Operation::removeChild(unique_ptr<Symbol>& child){
    child->setIndex(-1);
    for (int i = 0; i < children.size(); i ++){
        if (children[i] == child){
            shared_ptr<Expression> null;
            children[i]->setIndex(-1);
            children[i]->setParentExpression(null);
            children.erase(children.begin() + i);
            return;
        }
    }
    return;
}

void Operation::removeChild(int n){
    shared_ptr<Expression> null;
    children[n]->setIndex(-1);
    children[n]->setParentExpression(null);
    children.erase(children.begin() + n);
    return;
}

unique_ptr<Symbol>& Operation::getChild(int n){
    return children[n];
}

vector<unique_ptr<Symbol>>& Operation::getChildren(){
    return children;
}

vector<unique_ptr<Symbol>> Operation::duplicateChildren(){
    vector<unique_ptr<Symbol>> duplicates;
    for (int i = 0; i < children.size(); i ++){
        unique_ptr<Symbol> duplicate = children[i]->copy();
        duplicates.push_back(move(duplicate));
    }
    return duplicates;
}

vector<unique_ptr<Symbol>> Operation::duplicateChildren(int start, int end){
    vector<unique_ptr<Symbol>> duplicates;
    for (int i = start; i < end; i ++){
        unique_ptr<Symbol> duplicate = children[i]->copy();
        duplicates.push_back(move(duplicate));
    }
    return duplicates;
}

void Operation::expandExponent(Symbol* parent){return;}

void Operation::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){}

unique_ptr<Symbol> Operation::copy(){}

string Operation::toString(bool hasParent){return "";}

string Operation::toString(int depth, int offset){
    
    string str = "";
    int spaces = depth * offset;
    if (!sign){
        spaces -= 2;
    }
    for (int i = 0; i < spaces; i ++){
        str += ' ';
    }
    if (!sign){
        str += "-(";
        str += symbol;
        str += ')';
    }else{
        str += symbol;
    }
    
    depth ++;
    for (int i = 0; i < children.size(); i ++){
        str += '\n';
        str += children[i]->toString(depth, offset);
    }
    
    return str;


}


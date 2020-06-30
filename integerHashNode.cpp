#include "HashTables\integerHashNode.h"

IntegerHashNode::IntegerHashNode(): next(nullptr){}

IntegerHashNode::IntegerHashNode(int val): value(val), next(nullptr){}

int IntegerHashNode::getVal(){
    return value;
}

IntegerHashNode* IntegerHashNode::getNext(){
    return next;
}

void IntegerHashNode::setNext(IntegerHashNode* node){
    next = node;
}

bool IntegerHashNode::contains(int val){
    IntegerHashNode* current = this;
    while (this != nullptr){
        if (value == val){
            return true;
        }else{
            current = next;
        }
    }
    return false;
}

IntegerHashNode* IntegerHashNode::getLast(){
    IntegerHashNode* current = this;
    while (next != nullptr){
        current = next;
    }
    return current;
}
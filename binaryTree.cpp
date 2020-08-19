#include "Trees\binaryTree.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std;

BinaryTree::BinaryTree(){}

BinaryTree::BinaryTree(BinaryNodeBase* root): rootNode(root){}

BinaryNodeBase* BinaryTree::getRoot(){
    return rootNode;
}

BinaryNodeBase* BinaryTree::removeMainFunctionLeft(){
    BinaryNodeBase* newMain = rootNode->getLeftNode()->getLeftNode();
    if (newMain != 0){
        BinaryNodeBase* removed = rootNode->getLeftNode();
        removed->setLeftNode(0);
        rootNode->setLeftNode(newMain);
        return removed;
    }
    return 0;
}

BinaryNodeBase* BinaryTree::removeMainFunctionRight(){
    BinaryNodeBase* newMain = rootNode->getRightNode()->getRightNode();
    if (newMain != 0){
        BinaryNodeBase* removed = rootNode->getRightNode();
        removed->setRightNode(0);
        rootNode->setRightNode(newMain);
        return removed;
    }
    return 0;
}

void BinaryTree::insertNode(BinaryNodeBase& newNode){
    
}

void BinaryTree::insertNodeAtPosition(BinaryNodeBase* newNode, BinaryNodeBase* parent, Shift shift){
    BinaryNodeBase* oldChild;
    if (shift == Shift::LeftLeft){
        oldChild = parent->getLeftNode();
        parent->setLeftNode(newNode);
        newNode->setLeftNode(oldChild);
    }else if (shift == Shift::LeftRight){
        oldChild = parent->getLeftNode();
        parent->setLeftNode(newNode);
        newNode->setRightNode(oldChild);
    }else if (shift == Shift::RightRight){
        oldChild == parent->getRightNode();
        parent->setRightNode(newNode);
        newNode->setLeftNode(oldChild);
    }else if (shift == Shift::RightLeft){
        oldChild == parent->getRightNode();
        parent->setRightNode(newNode);
        newNode->setRightNode(oldChild);
    }
}

std::string BinaryTree::toString(){
    std::string treeStr = "";
    //rootNode->buildString(treeStr, -1);
    return treeStr;
}


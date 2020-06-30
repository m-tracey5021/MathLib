#include "Trees\binaryTree.h"
#include "Trees\operator.h"
#include "Trees\staticOperand.h"
#include <iostream>

BinaryTree::BinaryTree(){}

BinaryTree::BinaryTree(BinaryNode* root): rootNode(root){}

BinaryNode* BinaryTree::getRoot(){
    return rootNode;
}

void BinaryTree::initVariableCount(){
    variableCount = 0;
    rootNode->countVariables(variableCount);
}

void BinaryTree::simplifyEquation(char term){
    while (!variableIsIsolated()){

    }
}

bool BinaryTree::variableIsIsolated(){
    if (rootNode->getLeftNode()->isEmptyNode() & 
        rootNode->getLeftNode()->getElement()->getElementType() == "operand"){
        return true;
    }else{
        return false;
    }
}

BinaryNode* BinaryTree::removeMainFunctionLeft(){
    BinaryNode* newMain = rootNode->getLeftNode()->getLeftNode();
    if (newMain != 0){
        BinaryNode* removed = rootNode->getLeftNode();
        removed->setLeftNode(0);
        rootNode->setLeftNode(newMain);
        return removed;
    }
    return 0;
}

BinaryNode* BinaryTree::removeMainFunctionRight(){
    BinaryNode* newMain = rootNode->getRightNode()->getRightNode();
    if (newMain != 0){
        BinaryNode* removed = rootNode->getRightNode();
        removed->setRightNode(0);
        rootNode->setRightNode(newMain);
        return removed;
    }
    return 0;
}

void BinaryTree::insertMainFunctionLeft(Operator op, StaticOperand operand){
    BinaryNode* oldMain = rootNode->getLeftNode();
    BinaryNode* newMain = new BinaryNode();
    BinaryNode* newChild = new BinaryNode();
    
    newMain->setElement(&op);
    newMain->setLeftNode(newChild);
    newMain->setRightNode(oldMain);
    newMain->setParentNode(rootNode);

    newChild->setElement(&operand);
    newChild->setParentNode(newMain);

    rootNode->setLeftNode(newMain);
}

void BinaryTree::insertMainFunctionRight(Operator op, StaticOperand operand){
    BinaryNode* oldMain = rootNode->getRightNode();
    BinaryNode* newMain = new BinaryNode();
    BinaryNode* newChild = new BinaryNode();
    
    newMain->setElement(&op);
    newMain->setLeftNode(oldMain);
    newMain->setRightNode(newChild);
    newMain->setParentNode(rootNode);

    newChild->setElement(&operand);
    newChild->setParentNode(newMain);

    rootNode->setRightNode(newMain);

}


std::string BinaryTree::toString(){
    std::string treeStr = "";
    rootNode->buildString(treeStr, -1);
    return treeStr;
}


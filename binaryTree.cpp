#include "Trees\binaryTree.h"
#include <iostream>

BinaryTree::BinaryTree(){}

BinaryTree::BinaryTree(BinaryNode* root): rootNode(root){}

BinaryNode* BinaryTree::getRoot(){
    return rootNode;
}

void removeNode(BinaryNode* targetNode){
    //make sure balance is maintained somehow
}

void insertNode(BinaryNode* targetNode){
   // traverse tree to find node without two children, and add it as a new child 
}

char BinaryTree::findBranch(BinaryNode* targetNode){
    BinaryNode* tmpNode = targetNode;
    char side;
    bool done = false;
    while (done){
        if (tmpNode->getParentNode() != rootNode){
            tmpNode = tmpNode->getParentNode();
        }else if (tmpNode->getParentNode() == rootNode){
            if (rootNode->getLeftNode() == tmpNode){
                side = 'l';
                return side;
            }else if (rootNode->getRightNode() == tmpNode){
                side = 'r';
                return side;
            }else{
                // throw error
            }
        }else if (tmpNode->getParentNode() == nullptr){
            // will enter infinite loop here if node not part of a tree
            side = 'n';
            return side;
        }else{
            // throw error, something real fucked up happened
        }
    }
    return 'n';
}

/*

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

void BinaryTree::insertMainFunctionLeft(BinaryNode* targetOperation, BinaryNode* targetOperand){
    BinaryNode* oldMain = rootNode->getLeftNode();
    targetOperation->setParentNode(rootNode);
    targetOperation->
    
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
*/


std::string BinaryTree::toString(){
    std::string treeStr = "";
    rootNode->buildString(treeStr, -1);
    return treeStr;
}


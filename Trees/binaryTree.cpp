#include "binaryTree.h"

BinaryTree::BinaryTree(){}

BinaryTree::BinaryTree(unique_ptr<NodeBase>& rootNode): rootNode(move(rootNode)){}

void BinaryTree::setRoot(unique_ptr<NodeBase>& n){
    rootNode = move(n);
}

unique_ptr<NodeBase> BinaryTree::getRoot(){
    return move(rootNode);
}

// unique_ptr<NodeBase> BinaryTree::removeMainFunctionLeft(){
//     unique_ptr<NodeBase> newMain = rootNode->getLeftNode()->getLeftNode();
//     if (newMain != 0){
//         unique_ptr<NodeBase> removed = rootNode->getLeftNode();
//         removed->setLeft(0);
//         rootNode->setLeft(newMain);
//         return removed;
//     }
//     return 0;
// }

// unique_ptr<NodeBase> BinaryTree::removeMainFunctionRight(){
//     unique_ptr<NodeBase> newMain = rootNode->getRightNode()->getRightNode();
//     if (newMain != 0){
//         unique_ptr<NodeBase> removed = rootNode->getRightNode();
//         removed->setRight(0);
//         rootNode->setRight(newMain);
//         return removed;
//     }
//     return 0;
// }

// void BinaryTree::insertNode(BinaryNodeBase& newNode){
    
// }

// void BinaryTree::insertNodeAtPosition(unique_ptr<NodeBase> newNode, unique_ptr<NodeBase> parent, Shift shift){
//     unique_ptr<NodeBase> oldChild;
//     if (shift == Shift::LeftLeft){
//         oldChild = parent->getLeftNode();
//         parent->setLeft(newNode);
//         newNode->setLeft(oldChild);
//     }else if (shift == Shift::LeftRight){
//         oldChild = parent->getLeftNode();
//         parent->setLeft(newNode);
//         newNode->setRight(oldChild);
//     }else if (shift == Shift::RightRight){
//         oldChild == parent->getRightNode();
//         parent->setRight(newNode);
//         newNode->setLeft(oldChild);
//     }else if (shift == Shift::RightLeft){
//         oldChild == parent->getRightNode();
//         parent->setRight(newNode);
//         newNode->setRight(oldChild);
//     }
// }

std::string BinaryTree::toString(){
    std::string treeStr = "";
    //rootNode->buildString(treeStr, -1);
    return treeStr;
}


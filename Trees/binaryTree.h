#pragma once

#include "binaryNode.h"
#include <vector>

class BinaryTree {
    private:
        
    protected:
        BinaryNode* rootNode;
    public:
        BinaryTree();
        BinaryTree(BinaryNode* rootNode);

        BinaryNode* getRoot();
        BinaryNode* removeNode(BinaryNode* targetNode);
        void insertNode(BinaryNode* targetNode);
        char findBranch(BinaryNode* targetNode);

        std::string toString();


};
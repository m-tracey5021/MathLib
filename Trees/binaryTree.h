#pragma once

#include "binaryNode.h"
#include <vector>

class BinaryTree {
    private:
        BinaryNode* rootNode;
        BinaryNode* mainOperator;
        std::vector<BinaryNode> allNodes;
        std::vector<BinaryNode> emptyNodes;
        int variableCount;

    public:
        BinaryTree();
        BinaryTree(BinaryNode* rootNode);

        BinaryNode* getRoot();

        //void initVariableCount();
        //void simplifyEquation(char term);
        //bool variableIsIsolated();
    
        

        BinaryNode* removeMainFunctionLeft();
        BinaryNode* removeMainFunctionRight();
        //void insertMainNodeLeft(Operator op, StaticOperand operand);
        //void insertMainNodeRight(Operator op, StaticOperand operand);
        void insertNode(BinaryNode& newNode);
        void insertNodeAtPosition(BinaryNode* newNode, BinaryNode* parent, string insertionSide, string shift);
        std::string toString();


};
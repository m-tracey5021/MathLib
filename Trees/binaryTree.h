#pragma once

#include "binaryNode.h"
#include "operator.h"
#include "staticOperand.h"
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

        void initVariableCount();
        void simplifyEquation(char term);
        void isolateNode(BinaryNode* targetNode, char side);
        bool variableIsIsolated();

    
        BinaryNode* removeMainFunctionLeft();
        BinaryNode* removeMainFunctionRight();
        void insertMainFunctionLeft(Operator op, StaticOperand operand);
        void insertMainFunctionRight(Operator op, StaticOperand operand);

        std::string toString();


};
#pragma once

#include "binaryNodeBase.h"
#include "shift.h"
#include <vector>

using namespace std;

class BinaryTree {
    protected:
        BinaryNodeBase* rootNode;

    public:
        BinaryTree();
        BinaryTree(BinaryNodeBase* rootNode);

        BinaryNodeBase* getRoot();

        BinaryNodeBase* removeMainFunctionLeft();
        BinaryNodeBase* removeMainFunctionRight();
        void insertNode(BinaryNodeBase& newNode);
        void insertNodeAtPosition(BinaryNodeBase* newNode, BinaryNodeBase* parent, Shift shift);
        string toString();
};
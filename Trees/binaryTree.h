#pragma once

#include "../Containers/nodeBase.h"

using std::string;

class BinaryTree {
    
    protected:

        unique_ptr<NodeBase> rootNode;

    public:

        BinaryTree();

        BinaryTree(unique_ptr<NodeBase>& rootNode);

        void setRoot(unique_ptr<NodeBase>& n);

        unique_ptr<NodeBase> getRoot();

        // NodePtr removeMainFunctionLeft();

        // NodePtr removeMainFunctionRight();

        // void insertNode(BinaryNodeBase& newNode);

        // void insertNodeAtPosition(NodePtr newNode, NodePtr parent, Shift shift);

        string toString();
};
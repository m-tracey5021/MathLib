#pragma once

#include "treeNode.h"
#include "../Containers/nodeBase.h"

class Tree {
    
    protected:

        unique_ptr<NodeBase> root;

    public:

        Tree();

        Tree(unique_ptr<NodeBase>& root);

        


};
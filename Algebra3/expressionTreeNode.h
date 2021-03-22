#pragma once

#include "../Containers/dataContainer.h"
#include "../Containers/nodeBase.h"
#include "auxOp.h"
#include <memory>

using std::unique_ptr;

template<typename t>

class ExpressionTreeNode : public NodeBase {

    private:

        bool sign;
        
        unique_ptr<AuxOp> auxOp;

    public:
        
        ExpressionTreeNode();

        ExpressionTreeNode(DataContainer<t> data);

        ExpressionTreeNode(unique_ptr<AuxOp> auxOp);

        ExpressionTreeNode(DataContainer<t> data, unique_ptr<AuxOp> auxOp);

};
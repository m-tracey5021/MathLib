#pragma once

#include "../Containers/dataContainer.h"
#include "../Containers/nodeBase.h"

template<typename t>

class TreeNode : public NodeBase {

    private:

        DataContainer<t> data;

    public:

        TreeNode(): NodeBase(){}

        TreeNode(DataContainer<t>& data): NodeBase(), data(data){}

        TreeNode(unique_ptr<NodeBase>& parent, DataContainer<t>& data): NodeBase(), data(data){
            this->addUpstream(parent);
        }

        TreeNode(vector<unique_ptr<NodeBase>>& children, DataContainer<t>& data): NodeBase(children), data(data){}

        TreeNode(unique_ptr<NodeBase>& parent, vector<unique_ptr<NodeBase>>& children, DataContainer<t>& data): NodeBase(children), data(data){
            this->addUpstream(parent);
        }

        DataContainer<t> getData(){return data;}

        void setData(DataContainer<t>& d){data = d;}

};
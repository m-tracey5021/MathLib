#pragma once

#include "../Containers/dataContainer.h"
#include "../Containers/nodeBase.h"

template<typename t>

class BinaryNode : public NodeBase {

    private:

        DataContainer<t> data;
        
    public:

        BinaryNode(): NodeBase(){}

        BinaryNode(DataContainer<t>& data): NodeBase(), data(data){}

        BinaryNode(unique_ptr<NodeBase>& parent, DataContainer<t>& data): NodeBase(), data(data){
            this->addUpstream(parent);
        }

        BinaryNode(unique_ptr<NodeBase>& left, unique_ptr<NodeBase>& right, DataContainer<t>& data): NodeBase(), data(data){
            this->addDownstream(left);
            this->addDownstream(right);
        }   

        BinaryNode(unique_ptr<NodeBase>& parent, unique_ptr<NodeBase>& left, unique_ptr<NodeBase>& right, DataContainer<t>& data): NodeBase(children), data(data){
            this->addUpstream(parent);
            this->addDownstream(left);
            this->addDownstream(right);
        }

        DataContainer<t> getData(){return data;}
        
        void setData(DataContainer<t>& d){data = d;}

};
#pragma once

#include "../Containers/dataContainer.h"
#include "../Containers/nodeBase.h"

template<typename t>

class GraphNode : public NodeBase{

    private:

        DataContainer<t> data;

    public:

        GraphNode(): NodeBase{}

        GraphNode(DataContainer<t> data): NodeBase() data(data){}

        GraphNode(vector<unique_ptr<NodeBase>>& upstream, vector<unique_ptr<NodeBase>>& downstream, DataContainer<t> data): NodeBase(upstream, downstream), data(data){}

        DataContainer<t> getData(){return data;}
        
        void setData(DataContainer<t>& d){data = d;}


};
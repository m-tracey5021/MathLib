#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class GraphNodeBase;

typedef unique_ptr<GraphNodeBase> GraphNodePtr;

class GraphNodeBase {

    protected:

        vector<GraphNodePtr> connected;

    public:

        GraphNodeBase();

        GraphNodeBase(vector<GraphNodePtr>& connected);

        void connect(GraphNodePtr& toConnect);

        

};
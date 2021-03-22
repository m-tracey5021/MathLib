

#include "graphNodeBase.h"

GraphNodeBase::GraphNodeBase(){}

GraphNodeBase::GraphNodeBase(vector<GraphNodePtr>& connected): connected(move(connected)){}

void GraphNodeBase::connect(GraphNodePtr& toConnect){
    connected.push_back(move(toConnect));
}
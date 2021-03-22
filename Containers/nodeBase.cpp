#include "nodeBase.h"

NodeBase::NodeBase(){}

NodeBase::NodeBase(vector<unique_ptr<NodeBase>>& stream, bool up){
    up ? upstream = move(stream) : downstream = move(stream);
}

NodeBase::NodeBase(vector<unique_ptr<NodeBase>>& upstream, vector<unique_ptr<NodeBase>>& downstream): upstream(move(upstream)), downstream(move(downstream)){}

void NodeBase::addUpstream(unique_ptr<NodeBase>& up){
    upstream.push_back(move(up));
}

void NodeBase::addDownstream(unique_ptr<NodeBase>& down){
    downstream.push_back(move(down));
}
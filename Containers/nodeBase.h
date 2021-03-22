#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;
using std::move;

class NodeBase;

// typedef unique_ptr<NodeBase> unique_ptr<NodeBase>;

class NodeBase {

    protected:

        vector<unique_ptr<NodeBase>> upstream;

        vector<unique_ptr<NodeBase>> downstream;

    public:

        NodeBase();

        NodeBase(vector<unique_ptr<NodeBase>>& stream, bool up);

        NodeBase(vector<unique_ptr<NodeBase>>& upstream, vector<unique_ptr<NodeBase>>& downstream);

        void addUpstream(unique_ptr<NodeBase>& up);

        void addDownstream(unique_ptr<NodeBase>& down);

};

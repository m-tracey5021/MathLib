#pragma once

#include <string>
#include <utility>

using namespace std;

template<typename t>

class NodeInfo {
    private:
        pair<string, t> infoValue;
    public:
        NodeInfo(){}
        NodeInfo(pair<string, t> i){infoValue = i;}
        pair<string, t> getInfoValue(){return infoValue;}
};
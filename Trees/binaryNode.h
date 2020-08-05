#pragma once

#include <vector>
#include <string>
#include <utility>

using namespace std;

class BinaryNode {
    private:
    
    protected:
        BinaryNode* left; 
        BinaryNode* right;
        BinaryNode* parent;
        pair<string, string> infoTypeAndValue;
    public:
        BinaryNode();
        BinaryNode* getLeftNode();
        BinaryNode* getRightNode();
        BinaryNode* getParentNode();
        void setLeftNode(BinaryNode* node);
        void setRightNode(BinaryNode* node);
        void setParentNode(BinaryNode* node);
        bool isEmptyNode();
        //void countVariables(int count);
        int buildString(std::string& str, int index);
        void splitEquation(char* eq, int start, int end);
        //void addNodeTypeToCollection(std::vector<BinaryNode*> collection, std::string condition);
};
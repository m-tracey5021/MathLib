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
        pair<string, string> getInfoTypeAndValue();
        void setLeftNode(BinaryNode* node);
        void setRightNode(BinaryNode* node);
        void setParentNode(BinaryNode* node);
        void setInfoTypeAndValue(pair<string, string> info);
        bool isEmptyNode();
        //void countVariables(int count);
        int buildString(string& str, int index);
        void assignString(string& str, string instruction, int start, int end);
        //void splitEquation(char* eq, int start, int end);
        //void addNodeTypeToCollection(std::vector<BinaryNode*> collection, std::string condition);
};
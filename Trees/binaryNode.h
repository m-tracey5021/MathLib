#pragma once

#include "treeElement.h"
#include <vector>
#include <string>
#include <utility>

using namespace std;

class BinaryNode {
    private:
        BinaryNode* left; 
        BinaryNode* right;
        BinaryNode* parent;
        TreeElement* element;
        pair<string, string> infoTypeAndValue;
    public:
        BinaryNode();
        BinaryNode* getLeftNode();
        BinaryNode* getRightNode();
        BinaryNode* getParentNode();
        TreeElement* getElement();
        void setLeftNode(BinaryNode* node);
        void setRightNode(BinaryNode* node);
        void setParentNode(BinaryNode* node);
        void setElement(TreeElement* element);
        bool isEmptyNode();
        void countVariables(int count);
        int buildString(std::string& str, int index);
        void splitEquation(char* eq, int start, int end);
        void addNodeTypeToCollection(std::vector<BinaryNode*> collection, std::string condition);
};
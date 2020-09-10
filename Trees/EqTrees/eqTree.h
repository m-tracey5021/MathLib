#pragma once

#include "../binaryTree.h"
#include <vector>
#include <string>

using namespace std;

class EqTree : public BinaryTree {
    private:

    public:
        EqTree(){}
        EqTree(BinaryNodeBase* root): BinaryTree(root){}
        bool charIsOperator(char c);
        int* findSurroundingBrackets(string eq, int startPos);
        int* parseForMainOperator(string eq, int start, int end);
        vector<string> parseForOperands(string eq);
        //void assignEquation(string eq);

        int* (*operatorParsePointer)(string, int, int);
        int* (*operandsParsePointer)(string);
};
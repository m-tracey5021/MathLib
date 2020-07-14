

#include "Trees\binaryTree.h"
#include "Trees\EqTrees\eqTree.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;



EqTree createTreeFromEquation(char* eq, int size){

    BinaryNode* rootNode = new BinaryNode();
    EqTree tree(rootNode);

    rootNode->splitEquation(eq, 0, size);

    return tree;
}






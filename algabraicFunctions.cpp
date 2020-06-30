

#include "Trees\binaryTree.h"
#include "Trees\operator.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;



BinaryTree createTreeFromEquation(char* eq, int size){

    BinaryNode* rootNode = new BinaryNode();
    BinaryTree tree(rootNode);

    rootNode->splitEquation(eq, 0, size);

    return tree;
}






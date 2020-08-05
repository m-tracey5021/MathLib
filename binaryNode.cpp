#include "Trees\binaryNode.h"
#include "..\util.h"
#include <string>
#include <iostream>


BinaryNode::BinaryNode(){
    left = 0;
    right = 0;
    parent = 0;
}

BinaryNode* BinaryNode::getLeftNode(){
    return left;
}

BinaryNode* BinaryNode::getRightNode(){
    return right;
}

BinaryNode* BinaryNode::getParentNode(){
    return parent;
}

pair<string, string> BinaryNode::getInfoTypeAndValue(){
    return infoTypeAndValue;
}

void BinaryNode::setLeftNode(BinaryNode* node){
    left = node;
}

void BinaryNode::setRightNode(BinaryNode* node){
    right = node;
}

void BinaryNode::setParentNode(BinaryNode* node){
    parent = node;
}

void BinaryNode::setInfoTypeAndValue(pair<string, string> info){
    infoTypeAndValue = info;
}

bool BinaryNode::isEmptyNode(){
    if (left == nullptr & right == nullptr){
        return true;
    }else{
        return false;
    }
}

/*
void BinaryNode::countVariables(int count){
    if (element->isVariable()){
        count ++;
    }
    if (left != nullptr){
        right->countVariables(count);
    }
    if (right != nullptr){
        left->countVariables(count);
    }
    return;
}
*/

int BinaryNode::buildString(std::string& str, int index){
    int thisLength = 0;
    int leftLength = 0;
    int rightLength = 0;

    if (left != 0){
        leftLength = left->buildString(str, index);
    }
    index += leftLength;



    str += infoTypeAndValue.second;
    thisLength = infoTypeAndValue.second.length();
    index += thisLength;

    if (right != 0){
        rightLength = right->buildString(str, index);
    }
    index += rightLength;

    int totalSize = leftLength + thisLength + rightLength;

    if (infoTypeAndValue.first == "parenthesised"){
        str.insert(index - totalSize + 1, "(");
        index += 1;
        str.insert(index + 1, ")");
        index += 1;
        totalSize += 2;
    }

    return totalSize;
}

void BinaryNode::assignString(string& str, string instruction, int start, int end){
    if (instruction == "splitEquation"){
        int* operatorInfo = parseForMainOperator(str, start, end);
        int operatorIndex = operatorInfo[0];
        bool parenthesised = operatorInfo[1];

        if (operatorIndex != -1){
            //get operator here
            infoTypeAndValue.first = "operator";
            infoTypeAndValue.second = str[operatorIndex];
            BinaryNode* newLeft = new BinaryNode();
            BinaryNode* newRight = new BinaryNode();

            left = newLeft;
            right = newRight;
            left->setParentNode(this);
            right->setParentNode(this);

            left->assignString(str, instruction, start, operatorIndex);
            right->assignString(str, instruction, operatorIndex + 1, end);
        }else{
            // get value here
            infoTypeAndValue.first = "operand";
            infoTypeAndValue.second = ""; // call function here
            return;
        }
    }else if (instruction == "exampleInstruction") {
        // follow some other splitting rules
    }else{
        // throw error
    }
}

/*

void BinaryNode::splitEquation(char* eq, int start, int end){
    int* operatorInfo = parseForMainOperator(eq, start, end);
    int operatorIndex = operatorInfo[0];
    bool parenthesised = operatorInfo[1];
    
    if (operatorIndex != -1){
        //get operator here
        infoTypeAndValue.first = "operator";
        infoTypeAndValue.second = eq[operatorIndex];
        BinaryNode* newLeft = new BinaryNode();
        BinaryNode* newRight = new BinaryNode();

        left = newLeft;
        right = newRight;
        left->setParentNode(this);
        right->setParentNode(this);

        left->splitEquation(eq, start, operatorIndex);
        right->splitEquation(eq, operatorIndex + 1, end);
    }else{
        // get value here
        infoTypeAndValue.first = "operand";
        infoTypeAndValue.second = ""; // call function here
        return;
    }
}
*/



#pragma once

#include "binaryNodeBase.h"
#include "nodeInfo.h"
#include <vector>
#include <string>
#include <utility>

using namespace std;

template<typename t>

class BinaryNode {
    private:
        NodeInfo<t> nodeInfo;
        
    public:
        BinaryNode(): BinaryNodeBase(){}
        BinaryNode(NodeInfo<t> info): BinaryNodeBase(), nodeInfo(info){}

        NodeInfo<t> getNodeInfo(){return nodeInfo;}
        
        void setNodeInfo(NodeInfo<t> info){nodeInfo = info;}

        int buildString(string& str, int index){
            int thisLength = 0;
            int leftLength = 0;
            int rightLength = 0;

            if (left != 0){
                leftLength = left->buildString(str, index);
            }
            index += leftLength;

            str += nodeInfo.getInfoValue().second;
            thisLength = nodeInfo.getInfoValue().second.length();
            index += thisLength;

            if (right != 0){
                rightLength = right->buildString(str, index);
            }
            index += rightLength;

            int totalSize = leftLength + thisLength + rightLength;

            if (nodeInfo.getInfoValue().first == "parenthesised"){
                str.insert(index - totalSize + 1, "(");
                index += 1;
                str.insert(index + 1, ")");
                index += 1;
                totalSize += 2;
            }
            
            return totalSize;
        }

        template<typename i>
        void assignInfo(i* info, string instruction, int start, int end){
            if (instruction == "splitEquation"){
                int* operatorInfo = parseForMainOperator(info, start, end);
                int operatorIndex = operatorInfo[0];
                bool parenthesised = operatorInfo[1];

                if (operatorIndex != -1){
                    //get operator here
                    nodeInfo.getInfoValue().first = "operator";
                    nodeInfo.getInfoValue().second = info[operatorIndex];
                    BinaryNodeBase* newLeft = new BinaryNodeBase();
                    BinaryNodeBase* newRight = new BinaryNodeBase();

                    left = newLeft;
                    right = newRight;
                    left->setParentNode(this);
                    right->setParentNode(this);

                    left->assignString(info, instruction, start, operatorIndex);
                    right->assignString(info, instruction, operatorIndex + 1, end);
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

        void traverse(void (*traversalInstruction)(),  ){

        }   
        
        
};
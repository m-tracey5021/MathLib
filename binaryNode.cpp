#include "Trees\binaryNode.h"
#include "Trees\EqTrees\operator.h"
#include "Trees\EqTrees\staticOperand.h"
#include "util.h"
#include <cstring>
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

TreeElement* BinaryNode::getElement(){
    return element;
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

void BinaryNode::setElement(TreeElement* inputElement){
    element = inputElement;
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

    std::string s = typeid(element).name();

    str += element->toString();
    thisLength = stringLength(element->toString());
    index += thisLength;

    if (right != 0){
        rightLength = right->buildString(str, index);
    }
    index += rightLength;

    int totalSize = leftLength + thisLength + rightLength;

    if (element->isParenthesised()){
        str.insert(index - totalSize + 1, "(");
        index += 1;
        str.insert(index + 1, ")");
        index += 1;
        totalSize += 2;
    }

    return totalSize;
}

void BinaryNode::splitEquation(char* eq, int start, int end){
    int* operatorInfo = parseForMainOperator(eq, start, end);
    int operatorIndex = operatorInfo[0];
    bool parenthesised = operatorInfo[1];
    
    if (operatorIndex != -1){
        //Operator* mainOperator = new Operator(getOperatorType(eq[operatorIndex]), parenthesised, "operator");
        //element = mainOperator;
        element = new Operator(getOperatorType(eq[operatorIndex]), parenthesised, "operator");
        BinaryNode* newLeft = new BinaryNode();
        BinaryNode* newRight = new BinaryNode();
        //printNode(); 
        left = newLeft;
        right = newRight;
        left->setParentNode(this);
        right->setParentNode(this);

        left->splitEquation(eq, start, operatorIndex);
        right->splitEquation(eq, operatorIndex + 1, end);
    }else{
        //int staticVal = parseForFirstInt(eq, start, end);
        //StaticOperand* operand = new StaticOperand(parseForFirstInt(eq, start, end), "operand");
        //element = operand;
        element = parseForFirstOperand(eq, start, end);
        return;
    }
}

void BinaryNode::calculateResultantNode(Operator op, StaticOperand operand){
    TreeElement* nodeElement = this->getElement();

    bool removed = false;
    // check if operator is opposite
    if (nodeElement->getType() != nullptr){
        if (operatorTypeCancels(*nodeElement->getType(), *op.getType())){
            BinaryNode* newParent = this->getParentNode();
            BinaryNode* newChild = nullptr;

            // find child which is same as the input operand

            if (left->getElement()->getValue() != nullptr){
                if (*left->getElement()->getValue() == *operand.getValue()){
                    newChild = right;
                }
            }

            if (right->getElement()->getValue() != nullptr){
                if (*right->getElement()->getValue() == *operand.getValue()){
                    newChild = left;
                }
            }

            if (newChild != nullptr){
                if (newParent->getLeftNode() == this){
                    newParent->setLeftNode(newChild);
                }else if (newParent->getRightNode() == this){
                    newParent->setRightNode(newChild);
                }else{
                    // throw error
                }
                newChild->setParentNode(newParent);
                removed = true;
            }
        }
    }


    StaticOperand* result;
    if (nodeElement->getValue() != nullptr){
        if (*op.getType() == OperatorType::Addition){
            result = new StaticOperand(*nodeElement->getValue() + *operand.getValue(), "operand");
        }else if (*op.getType() == OperatorType::Subtraction){
            result = new StaticOperand(*nodeElement->getValue() - *operand.getValue(), "operand");
        }else if (*op.getType() == OperatorType::Multiplication){
            result = new StaticOperand(*nodeElement->getValue() * *operand.getValue(), "operand");
        }else if (*op.getType() == OperatorType::Division){
            result = new StaticOperand(*nodeElement->getValue() / *operand.getValue(), "operand");
        }else{
            // throw error
        }
        this->setElement(result);
    }
    

    if (left != nullptr){
        left->calculateResultantNode(op, operand);
    }
    if (right != nullptr){
        right->calculateResultantNode(op, operand);
    }
    if (right == nullptr & left == nullptr){
        return;
    }
}

void BinaryNode::addNodeTypeToCollection(std::vector<BinaryNode*> collection, std::string condition){
    if (condition.compare("allNodes") == 0){
        collection.push_back(this);
        if (left == 0 & right == 0){
            return;
        }else{
            left->addNodeTypeToCollection(collection, "allNodes");
            right->addNodeTypeToCollection(collection, "allNodes");
        }
    }else if (condition.compare("emptyNodes") == 0){
        if (left == 0 & right == 0){
            collection.push_back(this);
            return;
        }else{
            left->addNodeTypeToCollection(collection, "emptyNodes");
            right->addNodeTypeToCollection(collection, "emptyNodes");
        }
    }
}


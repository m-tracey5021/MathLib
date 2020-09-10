#pragma once

#include "../Trees/nodeInfo.h"
#include <vector>
#include <string>
#include <utility>

using namespace std;

class BinaryNodeBase {
    private:
    
    protected:
        BinaryNodeBase* left; 
        BinaryNodeBase* right;
        BinaryNodeBase* parent;
        
    public:
        BinaryNodeBase(){
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        BinaryNodeBase* getLeftNode(){return left;}
        BinaryNodeBase* getRightNode(){return right;}
        BinaryNodeBase* getParentNode(){return parent;}
        
        void setLeftNode(BinaryNodeBase* node){left = node;}
        void setRightNode(BinaryNodeBase* node){right = node;}
        void setParentNode(BinaryNodeBase* node){parent = node;}
        
        bool isEmptyNode(){
            if (left == nullptr & right == nullptr){
                return true;
            }else{
                return false;
            }
        } 
};
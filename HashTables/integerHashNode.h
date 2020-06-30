#pragma once

class IntegerHashNode{
    private:
        int value;
        IntegerHashNode* next; 
    public:
        IntegerHashNode();
        IntegerHashNode(int val);
        int getVal();
        IntegerHashNode* getNext();
        void setNext(IntegerHashNode* node);
        bool contains(int val);
        IntegerHashNode* getLast();

};
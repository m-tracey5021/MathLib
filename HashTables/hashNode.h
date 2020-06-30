#pragma once

template<class t>

class HashNode{
    private:
        t value;
        HashNode* next; 
    public:
        HashNode();
        HashNode(t val){
            value = val;
            next = nullptr;
        }

        int getVal(){return value;}
        HashNode* getNext(){return next;}
        void setNext(HashNode* node){next = node;}

        bool contains(t val){
            HashNode* current = this;
            while (this != nullptr){
                if (value == val){
                    return true;
                }else{
                    current = next;
                }
            }
            return false;
        }
        HashNode* getLast(){
            HashNode* current = this;
            while (next != nullptr){
                current = next;
            }
            return current;
        }

};
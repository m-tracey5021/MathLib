#pragma once

#include "hashSet.h"

template<typename t>

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

        t getVal(){return value;}

        HashNode* getNext(){return next;}

        void setNext(HashNode* node){next = node;}

        /*
        friend bool operator == (HashNode<t>& node1, HashNode<t>& node2){
            if (&node1 == nullptr & &node2 == nullptr){
                return true;
            }else if ((&node1 == nullptr & &node2 != nullptr) | (&node1 != nullptr & &node2 == nullptr)){
                return false;
            }else{
                if (node1.getVal() == node2.getVal()){
                    return true;
                }else{
                    return false;
                }
            }
        }
        */

       friend bool operator == (HashNode<t>& node1, HashNode<t>& node2){
            if (node1.getVal() == node2.getVal()){
                return true;
            }else{
                return false;
            }
        }

        friend bool operator != (HashNode<t>& node1, HashNode<t>& node2){
            if (node1.getVal() != node2.getVal()){
                return true;
            }else{
                return false;
            }
        }

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


/*
template<typename t>

class HashNode<HashSet<t>>{
    private:
        t value;
        HashNode* next; 
    public:
        HashNode();
        HashNode(t val){
            value = val;
            next = nullptr;
        }

        t getVal(){return value;}

        HashNode* getNext(){return next;}

        void setNext(HashNode* node){next = node;}

        friend bool operator == (const HashNode<HashSet<t>> hash1& const HashNode<HashSet<t>> hash2&){
            if (hash1 == hash)
        }

        friend bool operator != (const HashNode<HashSet<t>> hash1& const HashNode<HashSet<t>> hash2&){
            
        }

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
*/
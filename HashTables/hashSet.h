
#pragma once

#include "hashNode.h"
#include <string>

template<class t>

class HashSet {
    private:
        
    protected:
        int size;
        int numberOfNodes;
        HashNode<t>** table;
    public:
        HashSet(){}

        HashSet(int tableSize){
            size = tableSize;
            numberOfNodes = 0;
            table = new HashNode<t>*[tableSize]{};
            for (int i = 0; i < tableSize; i ++){
                table[i] = 0;
            }
        }

        HashSet(int tableSize, int inputSize, t inputArray[]){
            size = tableSize;
            numberOfNodes = 0;
            table = new HashNode<t>*[size]{};
            for (int i = 0; i < size; i ++){
                table[i] = nullptr;
            }
            for (int i = 0; i < inputSize; i ++){
                
                int index = inputArray[i] % size;
                HashNode<t>* previous = nullptr;
                HashNode<t>* current = table[index];
                HashNode<t>* newHash = new HashNode<t>(inputArray[i]);

                if (current != nullptr){
                    bool containsVal = false;
                    while (current != nullptr & !containsVal){
                        if (current->getVal() == inputArray[i]){
                            containsVal = true;
                        }else{
                            previous = current;
                            current = current->getNext();
                        }
                    }
                    if (!containsVal){
                        previous->setNext(newHash);
                        numberOfNodes ++;
                    }
            
                }else{
                    table[index] = newHash;
                    numberOfNodes ++;
                }


            }
        }

        int getSize(){return size;}
        int getNumberOfNodes(){return numberOfNodes;}
        HashNode<t>** getTable(){return table;}

        void insert(t val){
            int index = val % size;
            HashNode<t>* previous = nullptr;
            HashNode<t>* current = table[index];
            HashNode<t>* newHash = new HashNode<t>(val);
            
            if (current != nullptr){
                bool containsVal = false;
                while (current != nullptr & !containsVal){
                    if (current->getVal() == val){
                        containsVal = true;
                    }else{
                        previous = current;
                        current = current->getNext();
                    }
                }
                if (!containsVal){
                    
                    previous->setNext(newHash);
                    numberOfNodes ++;
                }
        
            }else{
                table[index] = newHash;
                numberOfNodes ++;
            }
        }

        void insert(int inputSize, t inputArray[]){
            for (int i = 0; i < inputSize; i ++){
                int index = inputArray[i] % size;
                HashNode<t>* previous = nullptr;
                HashNode<t>* current = table[index];
                HashNode<t>* newHash = new HashNode<t>(inputArray[i]);
                
                
                if (current != nullptr){
                    bool containsVal = false;
                    while (current != nullptr & !containsVal){
                        if (current->getVal() == inputArray[i]){
                            containsVal = true;
                        }else{
                            previous = current;
                            current = current->getNext();
                        }
                    }
                    if (!containsVal){
                        previous->setNext(newHash);
                        numberOfNodes ++;
                    }
            
                }else{
                    table[index] = newHash;
                    numberOfNodes ++;
                }
            }
        }

        void remove(t val){
            
        }

        bool contains(t val){
            int index = val % size;
            HashNode<t>* current = table[index];
            while (current != nullptr){
                if (current->getVal() == val){
                    return true;
                }
                current = current->getNext();
            }
            return false;
        }

        //template<typename t>
        t* toArray(){
            t* arr = new t[numberOfNodes]{};
            int posInArr = 0;
            for (int i = 0; i < size; i ++){
                HashNode<t>* current = table[i];
                while (current != nullptr){
                    arr[posInArr] = current->getVal();
                    posInArr ++;
                    current = current->getNext();
                }
            }
            return arr;
        }

        //template<typename t>
        std::string toString(){
            std::string str = "";
            for (int i = 0; i < size; i ++){
                str += "| - ";
                HashNode<t>* current = table[i];
                
                while (current != nullptr){
                    t val = current->getVal();
                    str += std::to_string(val) + " - ";
                    current = current->getNext();
                }
                str += "|";
            }
            return str;
        }



};
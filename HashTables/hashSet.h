
#pragma once

#include "hashNode.h"
#include <string>

template<typename t>

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

// specialisation for string

template<>

class HashSet<std::string> {
    private:
        
    protected:
        int size;
        int numberOfNodes;
        HashNode<std::string>** table;
    public:
        HashSet(){}

        HashSet(int tableSize){
            size = tableSize;
            numberOfNodes = 0;
            table = new HashNode<std::string>*[tableSize]{};
            for (int i = 0; i < tableSize; i ++){
                table[i] = 0;
            }
        }

        HashSet(int tableSize, int inputSize, std::string inputArray[]){
            size = tableSize;
            numberOfNodes = 0;
            table = new HashNode<std::string>*[size]{};
            for (int i = 0; i < size; i ++){
                table[i] = nullptr;
            }
            for (int i = 0; i < inputSize; i ++){
                
                int index = inputArray[i][0] % size;
                HashNode<std::string>* previous = nullptr;
                HashNode<std::string>* current = table[index];
                HashNode<std::string>* newHash = new HashNode<std::string>(inputArray[i]);

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
        HashNode<std::string>** getTable(){return table;}

        void insert(std::string val){
            int index = val[0] % size;
            HashNode<std::string>* previous = nullptr;
            HashNode<std::string>* current = table[index];
            HashNode<std::string>* newHash = new HashNode<std::string>(val);
            
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

        void insert(int inputSize, std::string inputArray[]){
            for (int i = 0; i < inputSize; i ++){
                int index = inputArray[i][0] % size;
                HashNode<std::string>* previous = nullptr;
                HashNode<std::string>* current = table[index];
                HashNode<std::string>* newHash = new HashNode<std::string>(inputArray[i]);
                
                
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

        void remove(std::string val){
            
        }

        bool contains(std::string val){
            int index = val[0] % size;
            HashNode<std::string>* current = table[index];
            while (current != nullptr){
                if (current->getVal() == val){
                    return true;
                }
                current = current->getNext();
            }
            return false;
        }

        std::string* toArray(){
            std::string* arr = new std::string[numberOfNodes]{};
            int posInArr = 0;
            for (int i = 0; i < size; i ++){
                HashNode<std::string>* current = table[i];
                while (current != nullptr){
                    arr[posInArr] = current->getVal();
                    posInArr ++;
                    current = current->getNext();
                }
            }
            return arr;
        }

        std::string toString(){
            std::string str = "";
            for (int i = 0; i < size; i ++){
                str += "| - ";
                HashNode<std::string>* current = table[i];
                
                while (current != nullptr){
                    std::string val = current->getVal();
                    str += val + " - ";
                    current = current->getNext();
                }
                str += "|";
            }
            return str;
        }



};
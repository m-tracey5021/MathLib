#include "HashTables/integerHashSet.h"
#include "util.h"
#include <string>


IntegerHashSet::IntegerHashSet(){}

IntegerHashSet::IntegerHashSet(int tableSize){
    size = tableSize;
    numberOfNodes = 0;
    table = new IntegerHashNode*[tableSize]{};
    for (int i = 0; i < tableSize; i ++){
        table[i] = 0;
    }
}

IntegerHashSet::IntegerHashSet(int tableSize, int inputSize, int inputArray[]){
    size = tableSize;
    numberOfNodes = 0;
    table = new IntegerHashNode*[size]{};
    for (int i = 0; i < size; i ++){
        table[i] = nullptr;
    }
    for (int i = 0; i < inputSize; i ++){
        
        int index = inputArray[i] % size;
        IntegerHashNode* previous = nullptr;
        IntegerHashNode* current = table[index];
        IntegerHashNode* newHash = new IntegerHashNode(inputArray[i]);

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

int IntegerHashSet::getSize(){
    return size;
}

int IntegerHashSet::getNumberOfNodes(){
    return numberOfNodes;
}

IntegerHashNode** IntegerHashSet::getTable(){
    return table;
}

void IntegerHashSet::insert(int val){
    
    int index = val % size;
    IntegerHashNode* previous = nullptr;
    IntegerHashNode* current = table[index];
    IntegerHashNode* newHash = new IntegerHashNode(val);
    
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

void IntegerHashSet::insert(int inputSize, int inputArray[]){
    for (int i = 0; i < inputSize; i ++){
        int index = inputArray[i] % size;
        IntegerHashNode* previous = nullptr;
        IntegerHashNode* current = table[index];
        IntegerHashNode* newHash = new IntegerHashNode(inputArray[i]);
        
        
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

void IntegerHashSet::remove(int val){

}

bool IntegerHashSet::contains(int val){
    int index = val % size;
    IntegerHashNode* current = table[index];
    while (current != nullptr){
        if (current->getVal() == val){
            return true;
        }
        current = current->getNext();
    }
    return false;
}

int* IntegerHashSet::toArray(){
    int* arr = new int[numberOfNodes]{};
    int posInArr = 0;
    for (int i = 0; i < size; i ++){
        IntegerHashNode* current = table[i];
        while (current != nullptr){
            arr[posInArr] = current->getVal();
            posInArr ++;
            current = current->getNext();
        }
    }
    return arr;
}

std::string IntegerHashSet::toString(){
    std::string str = "";
    for (int i = 0; i < size; i ++){
        str += "| - ";
        IntegerHashNode* current = table[i];
        
        while (current != nullptr){
            str += std::to_string(current->getVal()) + " - ";
            current = current->getNext();
        }
        str += "|";
    }
    return str;
}
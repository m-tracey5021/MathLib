#include "Sets/integerSet.h"

IntegerSet::IntegerSet(){}

IntegerSet::IntegerSet(int tableSize): IntegerHashSet(tableSize){}

IntegerSet::IntegerSet(int tableSize, int inputSize, int inputArray[]): IntegerHashSet(tableSize, inputSize, inputArray){}

int IntegerSet::getSize(){
    return size;
}

int IntegerSet::getNumberOfNodes(){
    return numberOfNodes;
}

IntegerHashNode** IntegerSet::getTable(){
    return table;
}

IntegerSet IntegerSet::setDifference(IntegerSet& other){
    IntegerSet setDiff(size);
    for (int i = 0; i < size; i ++){
        IntegerHashNode* current = table[i];
        if (current != nullptr){
            while (current != nullptr){
                int val = current->getVal();
                if (other.contains(val) == false){
                    setDiff.insert(val);
                }
                current = current->getNext();
            }
        }
    }
    return setDiff;
}

IntegerSet IntegerSet::setUnion(IntegerSet& other){
    IntegerSet setUnion(size + other.getSize());
    for (int i = 0; i < size; i ++){
        IntegerHashNode* current = table[i];
        if (current != nullptr){
            while (current != nullptr){
                int val = current->getVal();
                setUnion.insert(val);
                current = current->getNext();
            }
        }
    }
    for (int i = 0; i < other.getSize(); i ++){
        IntegerHashNode* current = other.getTable()[i];
        if (current != nullptr){
            while (current != nullptr){
                int val = current->getVal();
                setUnion.insert(val);
                current = current->getNext();
            }
        }
    }
    return setUnion;
}

IntegerSet IntegerSet::setIntersection(IntegerSet& other){
    IntegerSet setIntersection(size);
    for (int i = 0; i < size; i ++){
        IntegerHashNode* current = table[i];
        if (current != nullptr){
            while (current != nullptr){
                int val = current->getVal();
                if (other.contains(val) == true){
                    setIntersection.insert(val);
                }
                current = current->getNext();
            }
        }
    }
    return setIntersection;
}

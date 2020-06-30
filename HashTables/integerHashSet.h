
#pragma once

#include "integerHashNode.h"
#include <string>

//template<typename T>
class IntegerHashSet {
    private:
        
    protected:
        int size;
        int numberOfNodes;
        IntegerHashNode** table;
    public:
        IntegerHashSet();
        IntegerHashSet(int tableSize);
        IntegerHashSet(int tableSize, int inputSize, int inputArray[]);
        int getSize();
        int getNumberOfNodes();
        IntegerHashNode** getTable();
        void insert(int val);
        void insert(int inputSize, int inputArray[]);
        void remove(int val);
        bool contains(int val);
        int* toArray();
        std::string toString();



};
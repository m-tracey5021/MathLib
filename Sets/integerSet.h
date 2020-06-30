#pragma once

#include "..\HashTables\integerHashSet.h"

class IntegerSet : public IntegerHashSet{
    private:
        
    public:
        IntegerSet();
        IntegerSet(int tableSize);
        IntegerSet(int tableSize, int inputSize, int inputArray[]);
        int getSize();
        int getNumberOfNodes();
        IntegerHashNode** getTable();
        IntegerSet setDifference(IntegerSet& other);
        IntegerSet setUnion(IntegerSet& other);
        IntegerSet setIntersection(IntegerSet& other);

};
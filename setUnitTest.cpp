#include "Sets/set.h"
#include <string>

bool testSetDifference(){
    int toHash1[] = {1, 2, 3};
    int toHash2[] = {3, 4, 5};

    Set<int> set1(6, 3, toHash1);
    Set<int> set2(6, 3, toHash2);

    Set<int> setDiff1 = set1.setDifference(set2);
    std::string setDiffStr1 = setDiff1.toString();

    std::string expected1 = "| - || - 1 - || - 2 - || - || - || - |";

    if (setDiffStr1 == expected1){
        return true;
    }else{
        return false;
    }
}

bool testSetUnion(){
    int toHash1[] = {1, 2, 3};
    int toHash2[] = {3, 4, 5};

    Set<int> set1(6, 3, toHash1);
    Set<int> set2(6, 3, toHash2);

    Set<int> setUnion1 = set1.setUnion(set2);
    std::string setUnionStr1 = setUnion1.toString();

    std::string expected1 = "| - || - 1 - || - 2 - || - 3 - || - 4 - || - 5 - || - || - || - || - || - || - |";

    if (setUnionStr1 == expected1){
        return true;
    }else{
        return false;
    }
}

bool testSetIntersection(){
    int toHash1[] = {1, 39, 23, 33, 5};
    int toHash2[] = {1, 39, 41, 6, 70};
    int toHash3[] = {2, 2, 2, 5};

    Set<int> set1(12, 5, toHash1);
    Set<int> set2(10, 5, toHash2);
    Set<int> set3(8, 4, toHash3);

    std::string setStr1 = set1.toString();
    std::string setStr2 = set2.toString();
    std::string setStr3 = set3.toString();

    Set<int> intersection1 = set1.setIntersection(set2);
    Set<int> intersection2 = set1.setIntersection(set3);
    std::string setIntStr1 = intersection1.toString();
    std::string setIntStr2 = intersection2.toString();

    std::string expected1 = "| - || - 1 - || - || - 39 - || - || - || - || - || - || - || - || - |";
    std::string expected2 = "| - || - || - || - || - || - 5 - || - || - || - || - || - || - |";
    if (setIntStr1 == expected1 & setIntStr2 == expected2){
        return true;
    }else{
        return false;
    }
    
}

bool testStringSpecialisation(){
    std::string strings1[] = {"hippos", "are", "often", "hungry"};
    std::string strings2[] = {"giraffes", "tell", "lies", "often"};

    Set<std::string> set1(8, 4, strings1);
    Set<std::string> set2(8, 4, strings2);

    std::string setStr1 = set1.toString();
    std::string setStr2 = set2.toString();

    if (setStr1 == "| - hippos - hungry - || - are - || - || - || - || - || - || - often - |" & 
        setStr2 == "| - || - || - || - || - tell - lies - || - || - || - giraffes - often - |"){
        return true;
    }else{
        return false;
    }
}
#pragma once

#include <set>

namespace stdSet{
    
    template<typename T>
    std::set<T> setDifference(std::set<T> firstSet, std::set<T> secondSet){
        std::set<T> setDiff;
        for (T element : firstSet){
            if (secondSet.count(element) == 0){
                setDiff.insert(element);
            }
        }
        return setDiff;
    }

    template<typename T>
    std::set<T> setUnion(std::set<T> firstSet, std::set<T> secondSet){
        std::set<T> setUnion;
        for (T element : firstSet){
            setUnion.insert(element);
        }
        for (T element : secondSet){
            setUnion.insert(element);
        }
        return setUnion;
    }

    template<typename T>
    std::set<T> setIntersection(std::set<T> firstSet, std::set<T> secondSet){
        std::set<T> setIntersection;
        for (T element : firstSet){
            if (secondSet.count(element) == 1){
                setIntersection.insert(element);
            }
        }
        return setIntersection;
    }
}


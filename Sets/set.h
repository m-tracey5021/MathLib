#pragma once

#include "../HashTables/hashSet.h"

template<class t>

class Set : public HashSet<t>{
    private:
        
    public:
        Set(){}
        Set(int tableSize): HashSet<t>(tableSize){}
        Set(int tableSize, int inputSize, t inputArray[]): HashSet<t>(tableSize, inputSize, inputArray){}
        int getSize(){return this->size;}
        int getNumberOfNodes(){return this->numberOfNodes;}
        HashNode<t>** getTable(){return this->table;}

        Set setDifference(Set& other){
            Set<t> setDiff(this->size);
            for (int i = 0; i < this->size; i ++){
                HashNode<t>* current = this->table[i];
                if (current != nullptr){
                    while (current != nullptr){
                        t val = current->getVal();
                        if (other.contains(val) == false){
                            setDiff.insert(val);
                        }
                        current = current->getNext();
                    }
                }
            }
            return setDiff;
        }

        Set setUnion(Set& other){
            Set<t> setUnion(this->size + other.getSize());
            for (int i = 0; i < this->size; i ++){
                HashNode<t>* current = this->table[i];
                if (current != nullptr){
                    while (current != nullptr){
                        t val = current->getVal();
                        setUnion.insert(val);
                        current = current->getNext();
                    }
                }
            }
            for (int i = 0; i < other.getSize(); i ++){
                HashNode<t>* current = other.getTable()[i];
                if (current != nullptr){
                    while (current != nullptr){
                        t val = current->getVal();
                        setUnion.insert(val);
                        current = current->getNext();
                    }
                }
            }
            return setUnion;
        }

        Set setIntersection(Set& other){
            Set<t> setIntersection(this->size);
            for (int i = 0; i < this->size; i ++){
                HashNode<t>* current = this->table[i];
                if (current != nullptr){
                    while (current != nullptr){
                        t val = current->getVal();
                        if (other.contains(val) == true){
                            setIntersection.insert(val);
                        }
                        current = current->getNext();
                    }
                }
            }
            return setIntersection;
        }

};
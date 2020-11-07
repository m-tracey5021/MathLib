
#include <vector>
#include <string>
#include "bitString.h"
//#include "basicArithmeticFunctions.h"

using namespace std;

BitString::BitString(){}

BitString::BitString(vector<bool> initBits): bits(initBits){}

vector<bool> BitString::getBits(){
    return bits;
}

void BitString::setBits(vector<bool> newBits){
    bits = newBits;
}


string BitString::toString(){
    string toReturn = "";
    for (bool bit : bits){
        if (bit){
            toReturn += "1";
        }else{
            toReturn += "0";
        }
    }
    return toReturn;
}
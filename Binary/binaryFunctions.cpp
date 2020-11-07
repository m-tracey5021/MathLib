

#include <iostream>
#include <vector>
#include "bitString.h"
#include "../basicArithmeticFunctions.h"
using namespace std;


bool* binaryHalfAdd(bool first, bool second){

    bool sum = first ^ second;
    bool carry = first & second;
    bool* result = new bool[2]{sum, carry};
    return result;
}

bool* binaryFullAdd(bool first, bool second, bool carryIn){

    bool sum = first ^ second ^ carryIn;
    bool carryOut = (first & second) | (carryIn & (first ^ second));
    bool* result = new bool[2]{sum, carryOut};
    return result;
}

void padBits(BitString& toPad, int targetLength){
    int paddingLength = targetLength - toPad.getBits().size();
    if (paddingLength > 0){
        vector<bool> bits = toPad.getBits();
        for (int i = 0; i < paddingLength; i ++){
            bits.insert(bits.begin(), false);
        }
        toPad.setBits(bits);
    }
}

void padToSameLength(BitString& firstBits, BitString& secondBits){
    double bitDiff;
    if (firstBits.getBits().size() < secondBits.getBits().size()){
        padBits(firstBits, secondBits.getBits().size());
    }else if (firstBits.getBits().size() > secondBits.getBits().size()){
        padBits(secondBits, firstBits.getBits().size());
    }else{
        return;
    }
}

BitString reverseBits(BitString toReverse){
    
    vector<bool> reversedBits;
    for (bool bit : toReverse.getBits()){
        reversedBits.insert(reversedBits.begin(), bit);
    }
    BitString reversed(reversedBits);
    return reversed;
}


BitString convertToBin(int dec){
    vector<bool> bits;
    int tmpDec = dec;
    int result, remainder;
    bool done = false;

    while (done == false){
        result = tmpDec / 2;
        remainder = tmpDec % 2;
        bits.insert(bits.begin(), remainder);
        if (result < 1){
            done = true;
        }
        tmpDec = result;
    }

    return BitString(bits);

}

int convertToDecimal(BitString bitString){
    vector<bool> bits = bitString.getBits();
    int numberOfBits = bits.size();
    int total; 
    for (int i = 0; i < numberOfBits; i ++){
        int raiseTo = numberOfBits - 1 - i;
        double decToAdd = 0;
        if (bits[i]){
            decToAdd = power(2, raiseTo);
        }
        total += decToAdd;

    }
    return total;
}

BitString bitStringAdd(BitString firstBits, BitString secondBits){
    vector<bool> newBits;
    padToSameLength(firstBits, secondBits);
    int numberOfBits = firstBits.getBits().size();
    bool* firstBitResult = binaryHalfAdd(firstBits.getBits()[numberOfBits - 1], secondBits.getBits()[numberOfBits - 1]);
    bool firstSum = firstBitResult[0];
    bool carryIn = firstBitResult[1];
    newBits.insert(newBits.begin(), firstSum);
    for (int i = numberOfBits - 2; i >= 0; i -= 1){
        bool firstBitToAdd = firstBits.getBits()[i];
        bool secondBitToAdd = secondBits.getBits()[i];
        bool* fullAddResult = binaryFullAdd(firstBitToAdd, secondBitToAdd, carryIn);
        bool sum = fullAddResult[0];
        bool carryOut = fullAddResult[1];
        carryIn = carryOut;
        newBits.insert(newBits.begin(), sum);
        delete fullAddResult;
    }
    if (carryIn){
        newBits.insert(newBits.begin(), carryIn);
    }

    return newBits;
}

BitString addDecimalToBin(int firstInt, int secondInt){
    BitString bits1 = convertToBin(firstInt);
    BitString bits2 = convertToBin(secondInt);
    BitString result = bitStringAdd(bits1, bits2);
    return result;
}
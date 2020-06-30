#pragma once

#include "bitString.h"

bool* binaryHalfAdd(bool first, bool second);

bool* binaryFullAdd(bool first, bool second, bool carryIn);

void padBits(BitString& toPad, int targetLength);

void padToSameLength(BitString& firstBits, BitString& secondBits);

BitString reverseBits(BitString toReverse);

BitString convertToBin(int dec);

int convertToDecimal(BitString bitString);

BitString bitStringAdd(BitString firstBits, BitString secondBits);

BitString addDecimalToBin(int firstInt, int secondInt);
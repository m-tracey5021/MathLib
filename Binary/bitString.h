#pragma once

#include <vector>
#include <string>

class BitString {
    private:
        std::vector<bool> bits;
    public:
        BitString();
        BitString(std::vector<bool> initBits); 

        std::vector<bool> getBits();
        void setBits(std::vector<bool> newBits);
        std::string toString();

}; 
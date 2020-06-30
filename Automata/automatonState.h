#pragma once

#include <string>

class AutomatonState{
    private:
        std::string stateName;
        
    public:
        AutomatonState();
        AutomatonState(std::string sn);
        std::string getStateName();
};
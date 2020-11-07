#include "automatonState.h"

AutomatonState::AutomatonState(){}

AutomatonState::AutomatonState(std::string sn): stateName(sn){}

std::string AutomatonState::getStateName(){
    return stateName;
}
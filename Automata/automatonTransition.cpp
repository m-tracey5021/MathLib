#include "automatonTransition.h"

AutomatonTransition::AutomatonTransition(){}

AutomatonTransition::AutomatonTransition(AutomatonState* init, AutomatonState* result, char symbol): 
    inititalState(init), 
    resultState(result), 
    symbolRead(symbol){}

AutomatonState* AutomatonTransition::getInitState(){
    return inititalState;
}
AutomatonState* AutomatonTransition::getResultState(){
    return resultState;
}
char AutomatonTransition::getSymbolRead(){
    return symbolRead;
}
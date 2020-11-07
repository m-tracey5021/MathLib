#include "regex.h"
#include "regexElement.h"
#include "regexChar.h"
#include "regexString.h"
#include "regexUnion.h"
//#include "util.h"

Regex::Regex(){}

Regex::Regex(char* ia, int s): inputArr(ia), inputSize(s){
    //constructRegex(inputArr, 0, inputSize);
    constructMachine();
}

void Regex::constructMachine(){
    
}

FiniteAutomaton* Regex::constructConcatenation(char* inputArr, int inputSize){
    AutomatonState** states = new AutomatonState*[inputSize + 1];
    AutomatonState* startState = new AutomatonState("q0");
    AutomatonState* acceptState;
    AutomatonTransition** transitions = new AutomatonTransition*[inputSize];
    AutomatonState* current = startState;
    AutomatonState* previous = nullptr;
    for (int i = 1; i < inputSize; i ++){
        // set up symbols
        int tCounter = i - 1;
        char symbol = inputArr[tCounter];
        std::string stateName = "q" + std::to_string(i);

        // make new state
        AutomatonState* newState = new AutomatonState(stateName);
        if (i == inputSize - 1){
            acceptState = newState;
        }

        states[i] = newState;

        // make transition and move the head
        if (current != nullptr){
            if (previous != nullptr){
                AutomatonTransition* newTransition = new AutomatonTransition(previous, current, symbol);
                transitions[tCounter] = newTransition;
            }
            previous = current;
            current = newState;
        }else if (current == nullptr & previous == nullptr){
            current = newState;
        }else{
            //throw error
        }
    }
    FiniteAutomaton* concatMachine = new FiniteAutomaton(nullptr, 0, states, inputSize + 1, startState, acceptState, transitions, inputSize);


    return concatMachine;
    
}

FiniteAutomaton* Regex::constructUnion(char* firstArr, char* secondArr, int firstInputSize, int secondInputSize){
    int totalSize = firstInputSize + secondInputSize;
    AutomatonState** states = new AutomatonState*[totalSize + 1];
    AutomatonState* startState = new AutomatonState("q0");
    AutomatonState* acceptState = new AutomatonState("qAccept");
    states[0] = startState;

    AutomatonTransition** transitions = new AutomatonTransition*[totalSize];
    AutomatonState* current = startState;
    AutomatonState* previous = nullptr;
    char symbol;
    std::string stateName;
    int tCounter;
    for(int i = 1; i <= firstInputSize; i ++){
        // set up symbols
        tCounter = i - 1;
        symbol = inputArr[tCounter];
        stateName = "q" + std::to_string(i);
        AutomatonState* newState = new AutomatonState(stateName);
        states[i] = newState;

        if (current != nullptr){
            if (previous != nullptr){
                AutomatonTransition* newTransition = new AutomatonTransition(previous, current, symbol);
                transitions[tCounter] = newTransition;
            }
            previous = current;
            current = newState;
        }else if (current == nullptr & previous == nullptr){
            current = newState;
        }else{
            //throw error
        }
    }

    // reset pointers

    current = startState;
    previous = nullptr;

    for(int i = secondInputSize; i <= totalSize; i ++){
        // set up symbols
        symbol = inputArr[tCounter];
        stateName = "q" + std::to_string(i);
        AutomatonState* newState = new AutomatonState(stateName);
        states[i] = newState;
        
        if (current != nullptr){
            if (previous != nullptr){
                AutomatonTransition* newTransition = new AutomatonTransition(previous, current, symbol);
                transitions[tCounter] = newTransition;
            }
            previous = current;
            current = newState;
        }else if (current == nullptr & previous == nullptr){
            current = newState;
        }else{
            //throw error
        }

    }

    FiniteAutomaton* unionMachine = new FiniteAutomaton(nullptr, 0, states, totalSize + 1, startState, acceptState, transitions, totalSize);



    return unionMachine;
}

FiniteAutomaton* Regex::constructRepitition(char* inputArr, int inputSize, int repititions){
    AutomatonState** states = new AutomatonState*[inputSize + 1];
    AutomatonState* startState = new AutomatonState("q0");
    AutomatonState* acceptState = new AutomatonState("qAccept");
    states[0] = startState;

    AutomatonTransition** transitions = new AutomatonTransition*[inputSize];
    AutomatonState* current = startState;
    AutomatonState* previous = nullptr;

    FiniteAutomaton* tmpMachine = nullptr;
    FiniteAutomaton* repititionMachine = nullptr;
    for(int i = 0; i < repititions; i ++){
        tmpMachine = constructConcatenation(inputArr, inputSize);
        if (repititionMachine == nullptr){
            repititionMachine = tmpMachine;
        }else{
            repititionMachine = repititionMachine->concatenateAutomata(tmpMachine);
        }
    }
    return repititionMachine;
}



/*

void Regex::constructRegex(char* arr, int startIndex, int endIndex){
    RegexElement* start = nullptr;
    RegexElement* current = nullptr;

    int i = startIndex;

    while (i >= startIndex & i <= endIndex){
        char currentChar = arr[i];
        char nextChar;
        char nextNextChar;

        if (!(i + 1 > endIndex)){
            nextChar = arr[i + 1];
        }
        if (!(i + 2 > endIndex)){
            nextNextChar = arr[i + 2];
        }


        if (currentChar == '('){
            int* brackets = findSurroundingBrackets(inputArr, i);
            constructRegex(arr, brackets[0] + 1, brackets[1] - 1);
        }else{ // base case
            if (currentChar != 'v' & 
                    currentChar != '^' & 
                    currentChar != '/' & 
                    currentChar != ')'){
                if (nextChar == '/'){
                    if (nextNextChar == '^'){
                        int reps = findRepititions(arr, i + 3, endIndex);
                        RegexChar* newChar = new RegexChar(i, reps, arr[i]);
                        concatenateRegexElement(current, newChar, true);
                    }else if (nextNextChar == 'v'){

                    }
                }else{
                    RegexChar* newChar = new RegexChar(i, 1, currentChar);
                }
            }
        }   
    }
}


void Regex::concatenateRegexElement(RegexElement* currentElement, RegexElement* toConcat, bool sameElement){
    if (sameElement){
        currentElement->setChild(toConcat);
        toConcat->setParent(currentElement);
    }else{
        currentElement->setNext(toConcat);
        toConcat->setPrev(currentElement);
    }
}

int Regex::findRepititions(char* arr, int startIndex, int endIndex){
    int pos = startIndex;
    bool done = false;
    while(!done){
        if (arr[pos] == '/' | pos > endIndex){
            done = true;
        }else{
            pos ++;  
        }
    }
    int repititions = convertToInt(arr, startIndex + 1, pos);
    return repititions;
    
}

*/

FiniteAutomaton Regex::getMachine(){
    return machine;
}

char* Regex::getInputArr(){
    return inputArr;
}

int Regex::getInputSize(){
    return inputSize;
}

/*
RegexElement* Regex::getFirstElement(){
    return firstElement;
}
*/
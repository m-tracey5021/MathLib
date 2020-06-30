#pragma once

#include "regexElement.h"
#include "..\Automata\finiteAutomaton.h"

class Regex{
    private:
        FiniteAutomaton machine;
        char* inputArr;
        int inputSize;
        //RegexElement* firstElement;
    public:
        Regex();
        Regex(char* ia, int s);
        void constructMachine();
        
        //void constructRegex(char* chars, int startIndex, int endIndex);
        //void concatenateRegexElement(RegexElement* currentElement, RegexElement* toConcat, bool sameElement);
        //int findRepititions(char* arr, int startIndex, int endIndex);
        FiniteAutomaton getMachine();
        char* getInputArr();
        int getInputSize();
        FiniteAutomaton* constructConcatenation(char* inputArr, int inputSize);
        FiniteAutomaton* constructUnion(char* firstArr, char* secondArr, int firstInputSize, int secondInputSize);
        FiniteAutomaton* constructRepitition(char* inputArr, int inputSize, int repititions);
        //DFA* concatenateMachines(DFA other, AutomatonState* )
        //RegexElement* getFirstElement();

};
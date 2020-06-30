#pragma once

#include <string>
#include "..\Sets\set.h"
#include "automatonState.h"
#include "automatonTransition.h"

class FiniteAutomaton {
    private:
        Set<char>* alphabet;
        AutomatonState** states;
        AutomatonState* startState;
        AutomatonState* currentState;
        AutomatonState* acceptState;
        AutomatonTransition** transitions;
        int alphabetSize;
        int numberOfStates;
        int numberOfTransitions;
        

    public:
        FiniteAutomaton();
        FiniteAutomaton(Set<char>* a, int aSize, AutomatonState** s, int noStates, AutomatonState* ss, AutomatonState* as, AutomatonTransition** t, int noTrans);

        AutomatonState** getStates(){return states;}
        AutomatonState* getStartState(){return startState;}
        AutomatonState* getAcceptState(){return acceptState;}
        AutomatonTransition** getTransitions(){return transitions;}
        int getNumberOfStates(){return numberOfStates;}
        int getNumberOfTransitions(){return numberOfTransitions;}

        bool isDeterministic();
        void addState(AutomatonState* s);
        void addTransition(AutomatonTransition* t);
        AutomatonState* runTransition(AutomatonState* state, char symbol);
        bool run(char* input, int inputSize);
        FiniteAutomaton* concatenateAutomata(FiniteAutomaton* other);

};
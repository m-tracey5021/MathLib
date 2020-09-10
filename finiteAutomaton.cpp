#include "Automata/finiteAutomaton.h"
#include "Automata/automatonTransition.h"
#include "util.h"

FiniteAutomaton::FiniteAutomaton(){}

FiniteAutomaton::FiniteAutomaton(Set<char>* a, int aSize, AutomatonState** s, int noStates, AutomatonState* ss, AutomatonState* as, AutomatonTransition** t, int noTrans): 
    alphabet(a),
    alphabetSize(aSize),
    states(s),
    numberOfStates(noStates),
    startState(ss),
    currentState(ss),
    acceptState(as),
    transitions(t),
    numberOfTransitions(noTrans){}

bool FiniteAutomaton::isDeterministic(){
    for (int i = 0; i < numberOfTransitions - 1; i ++){
        for (int j = i + 1; j < numberOfTransitions; j ++){
            if (transitions[i]->getInitState() == transitions[j]->getInitState()){
                return false;
            }
        }
    }
    return true;
}

void FiniteAutomaton::addState(AutomatonState* s){
    AutomatonState** newStates = new AutomatonState*[numberOfStates + 1];
    for(int i = 0; i < numberOfStates + 1; i ++){
        if (i < numberOfStates){
            newStates[i] = states[i];
        }else{
            newStates[i] = s;
        }
    }
    states = newStates;
}

void FiniteAutomaton::addTransition(AutomatonTransition* t){
    AutomatonTransition** newTransitions = new AutomatonTransition*[numberOfTransitions + 1];
    for(int i = 0; i < numberOfTransitions + 1; i ++){
        if (i < numberOfTransitions){
            newTransitions[i] = transitions[i];
        }else{
            newTransitions[i] = t;
        }
    }
    transitions = newTransitions;
}

AutomatonState* FiniteAutomaton::runTransition(AutomatonState* state, char symbol){
    for (int i = 0; i < numberOfTransitions; i ++){

        AutomatonState* initState = transitions[i]->getInitState();
        AutomatonState* resultState = transitions[i]->getResultState();
        char onRead = transitions[i]->getSymbolRead();

        if (state == initState & symbol == onRead){
            return resultState;
        }
    }
    return nullptr;
}

bool FiniteAutomaton::run(char* input, int inputSize){
    for (int i = 0; i < inputSize; i ++){
        currentState = runTransition(currentState, input[i]);
    }
    if (currentState == acceptState){
        currentState = startState;
        return true;
    }else{
        currentState = startState;
        return false;
    }
}

FiniteAutomaton* FiniteAutomaton::concatenateAutomata(FiniteAutomaton* other){
    
    int totalStates = this->numberOfStates + other->getNumberOfStates() - 1;
    int totalTransitions = this->numberOfTransitions + other->getNumberOfTransitions();

    AutomatonState** concatStates = new AutomatonState*[totalStates];
    AutomatonTransition** concatTransitions = new AutomatonTransition*[totalTransitions];

    int stateCounter = 0;
    int transitionCounter = 0;
    int posInOther = 0;
    bool acceptPassed = false;
    while (!acceptPassed){
        
        concatTransitions[transitionCounter] = this->transitions[transitionCounter];
        transitionCounter ++;

        if (this->states[stateCounter] != this->acceptState){
            concatStates[stateCounter] = this->states[stateCounter];
            stateCounter ++;
        }else{
            concatTransitions[transitionCounter]->setResultState(other->getStates()[0]);
            acceptPassed = true;
        }
        
        
    }

    while (stateCounter <= totalStates){
        concatStates[stateCounter] = other->getStates()[posInOther];
        concatTransitions[transitionCounter] = other->getTransitions()[posInOther];
        stateCounter ++;
        transitionCounter ++;
    }

    AutomatonState* startState = concatStates[0];
    AutomatonState* acceptState = concatStates[totalStates];

    FiniteAutomaton* concatMachine = new FiniteAutomaton(nullptr, 0, concatStates, totalStates, startState, acceptState, concatTransitions, totalTransitions);
    return concatMachine;
}


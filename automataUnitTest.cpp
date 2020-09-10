#include "Automata/finiteAutomaton.h"
#include "Automata/automatonState.h"
#include "Automata/automatonTransition.h"

bool testThreeState(){
    //char* alpha = new char[2]{'0', '1'};

    char alphaArr[] = {'0', '1'};
    Set<char>* alpha = new Set<char>(4, 2, alphaArr);

    AutomatonState* startState = new AutomatonState("q1");
    AutomatonState* state2 = new AutomatonState("q2");
    AutomatonState* acceptState = new AutomatonState("q3");
    
    AutomatonTransition* t1 = new AutomatonTransition(startState, state2, '0');
    AutomatonTransition* t2 = new AutomatonTransition(state2, state2, '0');
    AutomatonTransition* t3 = new AutomatonTransition(state2, acceptState, '1');
    AutomatonTransition* t4 = new AutomatonTransition(acceptState, acceptState, '1');
    AutomatonTransition* t5 = new AutomatonTransition(acceptState, state2, '0');

    AutomatonState** states = new AutomatonState*[3]{startState, state2, acceptState};
    AutomatonTransition** transitions = new AutomatonTransition*[5]{t1, t2, t3, t4, t5};

    FiniteAutomaton automata(alpha, 2, states, 3, startState, acceptState, transitions, 5);

    char* input1 = new char[3]{'0', '1', '1'};
    char* input2 = new char[4]{'0', '0', '1', '0'};

    bool input1Accepted = automata.run(input1, 3);
    bool input2Accepted = automata.run(input2, 4);

    if (input1Accepted == true & input2Accepted == false){
        return true;
    }else{
        return false;
    }
}

bool testFiveState(){
    char alphaArr[] = {'0', '1'};
    Set<char>* alpha = new Set<char>(4, 2, alphaArr);

    AutomatonState* startState = new AutomatonState("q1");
    AutomatonState* state2 = new AutomatonState("q2");
    AutomatonState* state3 = new AutomatonState("q3");
    AutomatonState* state4 = new AutomatonState("q4");
    AutomatonState* acceptState = new AutomatonState("q5");

    AutomatonTransition* t1 = new AutomatonTransition(startState, state2, '0');
    AutomatonTransition* t2 = new AutomatonTransition(state2, state2, '1');
    AutomatonTransition* t3 = new AutomatonTransition(state2, state3, '0');
    AutomatonTransition* t4 = new AutomatonTransition(state3, state3, '1');
    AutomatonTransition* t5 = new AutomatonTransition(state3, acceptState, '0');
    AutomatonTransition* t6 = new AutomatonTransition(acceptState, acceptState, '1');
    AutomatonTransition* t7 = new AutomatonTransition(acceptState, state4, '0');
    AutomatonTransition* t8 = new AutomatonTransition(state4, acceptState, '1');

    AutomatonState** states = new AutomatonState*[5]{startState, state2, state3, state4, acceptState};
    AutomatonTransition** transitions = new AutomatonTransition*[8]{t1, t2, t3, t4, t5, t6, t7, t8};

    FiniteAutomaton automata(alpha, 2, states, 5, startState, acceptState, transitions, 8);

    char* input1 = new char[4]{'0', '1', '0', '0'};
    char* input2 = new char[5]{'0', '0', '0', '0', '1'};
    char* input3 = new char[10]{'0', '0', '0', '1', '1', '1', '1', '1', '1', '1'};
    char* input4 = new char[3]{'0', '1', '1'};

    bool input1Accepted = automata.run(input1, 4);
    bool input2Accepted = automata.run(input2, 5);
    bool input3Accepted = automata.run(input3, 10);
    bool input4Accepted = automata.run(input4, 3);

    if (input1Accepted == true &
        input2Accepted == true &
        input3Accepted == true &
        input4Accepted == false){
        return true;
    }else{
        return false;
    }


}

bool testSevenState(){
    return false;
}
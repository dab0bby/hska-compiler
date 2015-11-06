//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_STATE_H
#define HSKA_COMPILER_STATE_H

#include "Core.h"
#include "Transition.h"
#include "../../vector/vector.h"

class State
{
public:
    State();
    ~State();

    // Connects this state with another state through an epsilon transition.
    Transition connect(State &other);

    // Connects this state with another state through the specified condition.
    Transition connect(State other, char condition);

    vector<Transition> getTransitions();

    bool isFinalState();
    void setFinalState(bool isFinal);

    // Checks, which states can be reached through transitions that accept the input.
    // Returns the count of states that can be reached. All reached states are stored in the destinations array.
    vector<State*> findPaths(char input, bool addEpsilon = false);

private:
    vector<Transition> transitions;
    bool isFinal;

};

#endif //HSKA_COMPILER_STATE_H

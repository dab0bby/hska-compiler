//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_STATE_H
#define HSKA_COMPILER_STATE_H

#include "Core.h"
#include "Transitions.h"
#include "../../utils/header/vector.h"


class State
{
public:
    State();
    ~State();

    // Connects this state with another state through an epsilon transition.
    EpsilonTransition *connect(State &other);

    // Connects this state with another state through the specified condition.
    SingleCharTransition *connect(State other, char condition);

    // Connects this state with another state through the specified conditions.
    MultiCharTransition *connect(State other, char *conditions);

    vector<Transition*> getTransitions();

    bool isFinalState();
    void setFinalState(bool isFinal);

private:
    vector<Transition*> transitions;
    bool isFinal;

};

#endif //HSKA_COMPILER_STATE_H

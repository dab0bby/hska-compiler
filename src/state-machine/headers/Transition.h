//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_TRANSITION_H
#define HSKA_COMPILER_TRANSITION_H

#include "Core.h"

class Transition
{
public:
    Transition(State &first, State &second);
    Transition(State &first, State &second, char condition);

    State getFirstState();
    State getSecondState();
    char getCondition();
    bool isEpsilonTransition();

    bool operator ==(Transition other);

private:
    State *firstState, *secondState;
    char condition;
    bool empty;
};

#endif //HSKA_COMPILER_TRANSITION_H

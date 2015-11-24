//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_TRANSITION_H
#define HSKA_COMPILER_TRANSITION_H

#include "Core.h"
#include "../../utils/header/Helper.h"


// The base class for the different transitions. A Transition connects two states of a state machine.
class Transition
{
public:
    Transition(State &first, State &second);

    State *getFirstState();
    State *getSecondState();

    // Checks if the given char (input) passes this condition.
    virtual bool accepts(char input) = 0;

private:
    State *firstState, *secondState;
};

#endif //HSKA_COMPILER_TRANSITION_H

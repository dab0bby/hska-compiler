//
// Created by timo on 05.11.15.
//

#include "../headers/Transition.h"
#include "../../utils/header/Helper.h"

Transition::Transition(State &first, State &second)
{
    firstState = &first;
    secondState = &second;
}

State *Transition::getFirstState()
{
    return firstState;
}

State *Transition::getSecondState()
{
    return secondState;
}

//
// Created by timo on 05.11.15.
//

#include "../headers/Transition.h"

Transition::Transition(State &first, State &second)
{
    Transition(first, second);
    empty = true;
}

Transition::Transition(State &first, State &second, char condition)
{
    firstState = &first;
    secondState = &second;
    this->condition = condition;
}

State Transition::getFirstState()
{
    return *firstState;
}

State Transition::getSecondState()
{
    return *secondState;
}

char Transition::getCondition()
{
    return condition;
}

bool Transition::isEpsilonTransition()
{
    return empty;
};

bool Transition::operator ==(Transition other)
{
    return  (condition == other.condition) &&
            ((firstState == other.firstState && secondState == other.secondState) ||
            (firstState == other.secondState && secondState == other.firstState));
}
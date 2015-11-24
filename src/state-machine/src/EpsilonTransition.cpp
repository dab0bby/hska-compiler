//
// Created by timo on 24.11.15.
//

#include "../headers/EpsilonTransition.h"

EpsilonTransition::EpsilonTransition(State &first, State &second) : Transition(first, second)
{
}

bool EpsilonTransition::accepts(char input)
{
    return true;
}

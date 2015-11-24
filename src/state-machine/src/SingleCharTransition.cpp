//
// Created by timo on 24.11.15.
//

#include "../headers/SingleCharTransition.h"

SingleCharTransition::SingleCharTransition(State &first, State &second, char condition) : Transition(first, second)
{
    this->condition = condition;
}

char SingleCharTransition::getCondition()
{
    return condition;
}

bool SingleCharTransition::accepts(char input)
{
    return input == condition;
}

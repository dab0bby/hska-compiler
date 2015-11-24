//
// Created by timo on 24.11.15.
//

#include "../headers/MultiCharTransition.h"

MultiCharTransition::MultiCharTransition(State &first, State &second, char *conditions) : Transition(first, second)
{
    this->conditions = conditions;
    while(conditions[size + 1] != '\0') size++;
}

char *MultiCharTransition::getConditions()
{
    return conditions;
}

bool MultiCharTransition::accepts(char input)
{
    for (int i = 0; i < size; i++)
    {
        if (conditions[i] == input) return true;
    }

    return false;
}

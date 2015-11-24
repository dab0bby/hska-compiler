//
// Created by timo on 24.11.15.
//

#ifndef HSKA_COMPILER_MULTICHARTRANSITION_H
#define HSKA_COMPILER_MULTICHARTRANSITION_H

#include "Transition.h"

// A Transition that takes multiple conditions. Each char of the given string will be tested individually.
class MultiCharTransition : public Transition
{
public:
    MultiCharTransition(State &first, State &second, char *conditions);

    char *getConditions();

    // Checks if the given char (input) matches any of the chars in the condition.
    bool accepts(char input);

private:
    char *conditions;
    int size;
};


#endif //HSKA_COMPILER_MULTICHARTRANSITION_H

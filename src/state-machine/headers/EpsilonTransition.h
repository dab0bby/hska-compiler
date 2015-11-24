//
// Created by timo on 24.11.15.
//

#ifndef HSKA_COMPILER_EPSILONTRANSITION_H
#define HSKA_COMPILER_EPSILONTRANSITION_H


#include "../headers/Transition.h"

// A unconditionally Transition.
class EpsilonTransition : public Transition
{
public:
    EpsilonTransition(State &first, State &second);

    // This function is redundant and returns always true.
    // See Transition::accepts(char) for additional information.
    bool accepts(char input);
};


#endif //HSKA_COMPILER_EPSILONTRANSITION_H

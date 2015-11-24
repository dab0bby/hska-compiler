//
// Created by timo on 24.11.15.
//

#ifndef HSKA_COMPILER_SINGLECHARTRANSITION_H
#define HSKA_COMPILER_SINGLECHARTRANSITION_H

#include "Transition.h"

class SingleCharTransition : public Transition
{
public:
    SingleCharTransition(State &first, State &second, char condition);

    char getCondition();
    bool accepts(char input);

private:
    char condition;
};

#endif //HSKA_COMPILER_SINGLECHARTRANSITION_H

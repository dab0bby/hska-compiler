#pragma once

#include "Condition.h"

class TransitionTable
{
public:
    TransitionTable(int stateCount, Condition** conditions, int conditionCount);
    

private:
    const int Empty = -1;

    Condition** _conditions;
    int _conditionCount;
    int _stateCount;    
    
};

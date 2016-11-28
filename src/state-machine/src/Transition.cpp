//
// Created by timo on 05.11.15.
//

#include "../headers/Transition.h"
#include "../headers/State.h"
#include "../headers/Condition.h"


Transition::Transition(int target, const Condition* condition) :
    //_first(first),
    _target(target),
    _condition(const_cast<Condition*>(condition))
{
}

Transition::~Transition()
{
    delete _condition;
}
//
//int Transition::getFirstState() const 
//{
//    return _first;
//}

int Transition::getTarget() const
{
    return _target;
}

Condition* Transition::getCondition() const
{
    return _condition;
}

bool Transition::accepts(char input)
{
    return _condition->accepts(input);
}

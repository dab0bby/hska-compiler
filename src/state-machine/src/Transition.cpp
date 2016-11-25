//
// Created by timo on 05.11.15.
//

#include "../headers/Transition.h"
#include "../headers/State.h"
#include "../headers/Condition.h"


Transition::Transition(State* first, const State* second, const Condition& condition) :
    _first(first),
    _second(const_cast<State*>(second)),
    _condition(const_cast<Condition&>(condition))
{
}

Transition::~Transition()
{
}

State* Transition::getFirstState() const 
{
    return _first;
}

State* Transition::getSecondState() const
{
    return _second;
}

Condition& Transition::getCondition() const
{
    return _condition;
}

bool Transition::accepts(char input)
{
    return _condition.accepts(input);
}

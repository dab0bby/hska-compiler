//
// Created by timo on 05.11.15.
//

#include "../headers/Transition.h"
#include "../headers/State.h"
#include "../headers/Condition.h"

Transition::Transition() : _first(State::empty), _second(State()), _condition(EpsilonCondition())
{
    
}

Transition::Transition(State& first, const State& second, const Condition& condition) : _first(first), _second(second), _condition(condition)
{    
    _first.addTransition(*this);
}

Transition::~Transition()
{
    _first.removeTransition(*this);
}

const State& Transition::getFirstState() const 
{
    return _first;
}

const State& Transition::getSecondState() const
{
    return _second;
}

const Condition& Transition::getCondition() const
{
    return _condition;
}

bool Transition::accepts(char input)
{
    return _condition.accepts(input);
}

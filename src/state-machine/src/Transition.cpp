//
// Created by timo on 05.11.15.
//
#pragma once

#include "../include/Transition.h"
#include "../include/State.h"


Transition::Transition(const Transition& other)
{
    _target = other._target;
    _condition = other._condition->clone();
}

Transition::Transition(int target, const Condition* condition) :
    //_first(first),
    _target(target),
    _condition(const_cast<Condition*>(condition))
{
}

Transition::~Transition()
{
    delete _condition;
    _condition = nullptr;
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

bool Transition::accepts(char input) const
{
    return _condition->accepts(input);
}

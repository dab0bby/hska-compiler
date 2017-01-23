//
// Created by timo on 05.11.15.
//


#include "../include/Transition.h"
#include "../include/Condition.h"


Transition::Transition(): _target(-1), _condition(nullptr)
{
}

Transition::Transition(const Transition& other)
{
    operator=(other);
}

Transition::Transition(Transition&& other) noexcept
{
    _target = other._target;
    _condition = other._condition;

    // prevent deletion of condition
    other._condition = nullptr;
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

Transition& Transition::operator=(Transition&& other) noexcept
{
    _target = other._target;
    _condition = other._condition;

    // prevent deletion of condition
    other._condition = nullptr;
    return *this;
}

Transition& Transition::operator=(const Transition& other) noexcept
{
    _target = other._target;
    _condition = other._condition->clone();
    return *this;
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

//
// Created by timo on 05.11.15.
//

#include "../headers/State.h"

State State::empty = State();

State::State() : token(0), _isFinal(false)
{
}

State::State(bool isFinal) : _isFinal(isFinal), token(0)
{    
}

State::State(bool isFinal, int token) : State(isFinal)
{
    this->token = token;
}

State::State(State& other, Condition& condition, bool isFinal, int token) : State(other, condition, isFinal)
{
    this->token = token;
}

State::State(State& other, Condition& condition, bool isFinal) : State(isFinal)
{
    connect(other, condition);
}

State::~State()
{
   // delete _transitions;
}

Transition& State::connect(const State& other, const Condition& condition)
{
    auto t = Transition(*this, other, condition);
    addTransition(t);
    return t;
}

vector<Transition> State::getTransitions() const
{
    return _transitions;
}

bool State::isFinalState() const
{
    return _isFinal;
}

void State::setFinalState(bool isFinal)
{
    this->_isFinal = isFinal;
}

void State::addTransition(const Transition& t)
{
    _transitions.add(t);
}

void State::removeTransition(const Transition& t)
{
    _transitions.remove(t);
}

bool State::accepts(char input, State& next) const
{
    for (int i = 0; i < _transitions.size(); i++)
    {
        if (_transitions[i].accepts(input))
        {
            next = _transitions[i].getSecondState();
            return true;
        }
    }

    return false;
}

bool State::hasTransitions() const
{
    return _transitions.size() > 0;
}

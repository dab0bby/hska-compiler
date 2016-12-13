//
// Created by timo on 05.11.15.
//

#include "../include/State.h"
#include <iostream>

State State::empty = State();

State::State() : token(0), _isFinal(false)
{
}

State::State(bool isFinal) : token(0), _isFinal(isFinal)
{
}

State::State(bool isFinal, int token) : State(isFinal)
{
    this->token = token;
}

State::State(int other, Condition* condition, bool isFinal, int token) : State(other, condition, isFinal)
{
    this->token = token;
}

State::State(int other, Condition* condition, bool isFinal) : State(isFinal)
{
    connect(other, condition);
}

State::~State()
{
   // delete _transitions;
}

Transition* State::connect(int other, const Condition* condition)
{
    auto t = new Transition(other, condition);
    addTransition(t);
    return t;
}

vector<Transition*> State::getTransitions() const
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

void State::addTransition(const Transition* t)
{
    _transitions.push_back(const_cast<Transition* const&>(t));
}

void State::removeTransition(Transition const*  t)
{
    //_transitions.remove(const_cast<Transition* const&>(t));

}

bool State::accepts(char input, int& next) const
{
    //cout << "checking for " << Token::getTokenName(token);

    for (int i = 0; i < _transitions.size(); i++)
    {
        if (_transitions[i]->accepts(input))
        {
            next = _transitions[i]->getTarget();
        //    cout << " accept" << endl;
            return true;
        }
    }

    //cout << " faield" << endl;
    return false;
}

bool State::hasTransitions() const
{
    return _transitions.size() > 0;
}

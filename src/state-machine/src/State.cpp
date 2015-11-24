//
// Created by timo on 05.11.15.
//

#include "../headers/State.h"

State::State()
{
    transitions = *(new vector<Transition*>());
}

State::~State()
{
}

EpsilonTransition *State::connect(State &other)
{
    EpsilonTransition *t = new EpsilonTransition(*this, other);
    for (int i = 0; i < transitions.size(); i++)
    {
        if (transitions.get(i) == t)
        {
            delete t;
            return static_cast<EpsilonTransition*>(transitions[i]);
        }
    }
    return t;
}

SingleCharTransition *State::connect(State other, char condition)
{
    SingleCharTransition *t = new SingleCharTransition(*this, other, condition);
    for (int i = 0; i < transitions.size(); i++)
    {
        if (transitions.get(i) == t)
        {
            delete t;
            return static_cast<SingleCharTransition*>(transitions[i]);
        }
    }
    return t;
}


MultiCharTransition *State::connect(State other, char *conditions)
{
    MultiCharTransition *t = new MultiCharTransition(*this, other, conditions);
    for (int i = 0; i < transitions.size(); i++)
    {
        if (transitions.get(i) == t)
        {
            delete t;
            return static_cast<MultiCharTransition*>(transitions[i]);
        }
    }
    return t;
}

vector<Transition*> State::getTransitions()
{
    return transitions;
}

bool State::isFinalState()
{
    return isFinal;
}

void State::setFinalState(bool isFinal)
{
    this->isFinal = isFinal;
}

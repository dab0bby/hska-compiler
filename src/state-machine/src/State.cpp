//
// Created by timo on 05.11.15.
//

#include "../headers/State.h"

State::State()
{
    transitions = *(new vector<Transition>());
}

State::~State()
{
}

Transition State::connect(State &other)
{
    Transition *t = new Transition(*this, other);
    for (int i = 0; i < transitions.size(); i++)
    {
        if (transitions.get(i) == *t)
        {
            delete t;
            return transitions[i];
        }
    }
    return *t;
}

Transition State::connect(State other, char condition)
{
    Transition *t = new Transition(*this, other, condition);
    for (int i = 0; i < transitions.size(); i++)
    {
        if (transitions.get(i) == *t)
        {
            delete t;
            return transitions[i];
        }
    }
    return *t;
}

vector<Transition> State::getTransitions()
{
    return transitions;
}

bool State::isFinalState()
{
    return isFinal;
}

vector<State*> State::findPaths(char input, bool allowEpsilon)
{
    vector<State*> destinations = *(new vector<State*>());
    for (int i = 0; i < transitions.size(); i++)
    {
        // check if transition's condition is matched or if it is an epsilon transition
        if (transitions[i].getCondition() == input || (transitions[i].isEpsilonTransition() && allowEpsilon))
        {
            // add the state from the other side of the transition
            destinations.add((transitions[i].getFirstState() == this) ? transitions[i].getSecondState() : transitions[i].getFirstState());
        }
    }
    return destinations;
}

void State::setFinalState(bool isFinal)
{
    this->isFinal = isFinal;
}

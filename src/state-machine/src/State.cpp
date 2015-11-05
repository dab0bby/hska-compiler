//
// Created by timo on 05.11.15.
//

#include "../headers/State.h"

State::State()
{
    transitions = new vector<Transition>();
}

State::~State()
{
}

Transition State::connect(State &other)
{
    Transition *t = new Transition(*this, other);
    for (int i = 0; i < transitions->size(); i++)
    {
        if (transitions->get(i) == *t)
        {
            delete t;
            return (*transitions)[i];
        }
    }
    return *t;
}

Transition State::connect(State other, char condition)
{
    Transition *t = new Transition(*this, other, condition);
    for (int i = 0; i < transitions->size(); i++)
    {
        if (transitions->get(i) == *t)
        {
            delete t;
            return (*transitions)[i];
        }
    }
    return *t;
}

vector<Transition> State::getTransitions()
{
    return new vector<Transition>(transitions);  // todo: WHY?!?!?
}

bool State::isFinalState()
{
    return false;
}

int State::findPaths(char input, State *destinations)
{
    return 0;
}

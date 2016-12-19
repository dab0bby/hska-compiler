/**
 * StateMachine.cpp
 */

#include "../include/StateMachine.h"
#include <iostream>


StateMachine::StateMachine(vector<State*> states, int initialState) :
    _initialState(initialState),
    _currentState(initialState),
    _states(states)
{
}


//StateMachine::StateMachine(State& initialState, Token::TokenType token) : StateMachine(initialState)
//{
//    this->token = token;
//}

bool StateMachine::forward(char input)
{
    return _states[_currentState]->accepts(input, _currentState);
}

void StateMachine::reset()
{
 //   cout << "inital state: " << Token::getTokenName(_initialState.token) << endl;
    _currentState = _initialState;
}

bool StateMachine::canForward() const
{
    return _states[_currentState]->hasTransitions();
}

bool StateMachine::isFinal() const
{
    return _states[_currentState]->isFinalState();
}

bool StateMachine::isInInitialState() const
{
    return _currentState == _initialState;
}

int StateMachine::getCurrentToken() const
{
    return _states[_currentState]->token;
}

StateMachine::~StateMachine()
{
    for (int i = 0; i < _states.size(); i++)
    {
        delete _states[i];
        _states[i] = nullptr;
    }
}

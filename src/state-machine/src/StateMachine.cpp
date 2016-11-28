/**
 * StateMachine.cpp
 */

#include "../headers/StateMachine.h"
#include <iostream>
#include "../../scanner/include/Token.h"


StateMachine::StateMachine(vector<State*> states, int initialState) : _states(states), _initialState(initialState), _currentState(initialState)
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

bool StateMachine::forecast(char input, int& token) const
{
    int tmp = _currentState;
    auto r = _states[_currentState]->accepts(input, tmp);
    token = _states[tmp]->token;
    return r;
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

int StateMachine::getCurrentToken() const
{
    return _states[_currentState]->token;
}

StateMachine::~StateMachine()
{

}

/**
 * StateMachine.cpp
 */

#include "../headers/StateMachine.h"


StateMachine::StateMachine(State& initialState) : _initialState(initialState), _currentState(initialState)
{
}

//StateMachine::StateMachine(State& initialState, Token::TokenType token) : StateMachine(initialState)
//{
//    this->token = token;
//}

bool StateMachine::forward(char input) const
{
    return _currentState.accepts(input, _currentState);
}

bool StateMachine::forecast(char input, int& token) const
{
    State tmp = _currentState;
    auto r = _currentState.accepts(input, tmp);
    token = tmp.token;
    return r;
}

void StateMachine::reset()
{
    _currentState = _initialState;
}

bool StateMachine::canForward() const
{
    return _currentState.hasTransitions();
}

bool StateMachine::isFinal() const
{
    return _currentState.isFinalState();
}

int StateMachine::getCurrentToken() const
{
    return _currentState.token;
}

StateMachine::~StateMachine()
{

}

void StateMachine::setInitialState(State& state)
{
    _initialState = state;
}

State& StateMachine::getInitialState() const
{
    return _initialState;
}

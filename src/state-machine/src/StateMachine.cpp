/**
 * StateMachine.cpp
 */

#include "../include/StateMachine.h"
#include <cstring>
#include <exception>

StateMachine::StateMachine(int stateCount, int initialState, int finalState, Token::TokenType token) :
    StateMachine(stateCount, initialState, new int[1]{ finalState }, finalState, token)
{
}

StateMachine::StateMachine(int stateCount, int initialState, int* finalStates, int finalStatesCount, Token::TokenType token) :
_initialState(initialState),
_stateCount(stateCount),
_transitions(new Transition*[stateCount]),
_transitionCounts(new int[stateCount]{0}),
_finalStates(finalStates),
_finalStatesCount(finalStatesCount),
_token(token)
{
}

StateMachine::~StateMachine()
{
    for (int i = 0; i < _stateCount; i++)
        if (_transitionCounts[i] > 0)
            delete[] _transitions[i];

    delete[] _transitions;
    delete[] _transitionCounts;    
    delete[] _finalStates;
}

bool StateMachine::process(char input)
{
    processed++;

    for (int i = 0; i < _transitionCounts[_currentState]; i++)
    {
        auto t = &_transitions[_currentState][i];
        if (t->accepts(input))
        {
            _currentState = t->getTarget();
            return true;
        }
    }

    return false;
}

void StateMachine::reset()
{
    _currentState = _initialState;
    processed = 0;
}

void StateMachine::reset(int startPosition)
{
    reset();
    this->startPosition = startPosition;
}

void StateMachine::setTransitions(int state, Transition&& transition) const
{
    setTransitions(state, new Transition[1]{ transition }, 1);
}

void StateMachine::setTransitions(int state, Transition* transitions, int count) const
{
    _transitions[state] = transitions;
    _transitionCounts[state] = count;
}

void StateMachine::getTransitions(int state, Transition*& transitions, int& count) const
{
    transitions = _transitions[state];
    count = _transitionCounts[state];
}

bool StateMachine::canProcess() const
{
    return _transitionCounts[_currentState] > 0;
}

bool StateMachine::isInFinalState() const
{
    for (int i = 0; i < _finalStatesCount; i++)
        if (_currentState == _finalStates[i])
            return true;

    return false;
}

bool StateMachine::isInInitialState() const
{
    return _currentState == _initialState;
}

Token::TokenType StateMachine::getToken() const
{
    return _token;
}

int StateMachine::getCurrentState() const
{
    return _currentState;
}

StateMachine* StateMachine::createAtomic(Token::TokenType token)
{
    return new StateMachine(2, 0, new int[1]{ 1 }, 1, token);
}

StateMachine* StateMachine::createAtomic(Token::TokenType token, Condition* condition)
{
    auto sm = new StateMachine(2, 0, new int[1]{ 1 }, 1, token);
    sm->setTransitions(0, new Transition[1]{ Transition(1, condition) }, 1);
    return sm;
}

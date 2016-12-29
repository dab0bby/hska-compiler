/**
 * StateMachine.h
 */

#ifndef StateMachine_H_
#define StateMachine_H_

#include "../../scanner/include/Token.h"
#include "Transition.h"

class StateMachine
{
public:
    StateMachine(int stateCount, int initialState, int finalState, Token::TokenType token);
    StateMachine(int stateCount, int initialState, int* finalStates, int finalStatesCount, Token::TokenType token);
    ~StateMachine();

    bool process(char input);
    void reset();
    void reset(int startPosition);
    void setTransitions(int state, Transition&& transition) const;
    void setTransitions(int state, Transition* transitions, int count) const;
    void getTransitions(int state, Transition*& transitions, int& count) const;

    bool canProcess() const;
    bool isInFinalState() const;
    bool isInInitialState() const;
    Token::TokenType getToken() const;
    int getCurrentState() const;

    static StateMachine* createAtomic(Token::TokenType token);
    static StateMachine* createAtomic(Token::TokenType token, Condition* condition);

    int startPosition = 0;
    int processed = 0;

private:
    int _initialState;
    int _currentState = 0;
    int _stateCount;
    Transition** _transitions;
    int* _transitionCounts;
    int* _finalStates;
    int _finalStatesCount;
    Token::TokenType _token;

};

#endif /* StateMachine_H_ */

/**
 * StateMachine.h
 */

#ifndef StateMachine_H_
#define StateMachine_H_

#include "State.h"

class StateMachine
{
public:
    explicit StateMachine(State& initialState);
    //StateMachine(State& initialState, Token::TokenType token);
    ~StateMachine();
    
    void setInitialState(State& state);
    State& getInitialState() const;
    bool forward(char input) const;
    bool forecast(char input, int& token) const;
    void reset();
    bool canForward() const;  
    bool isFinal() const;
    int getCurrentToken() const;
    
private:
    State& _initialState;
    State& _currentState;
    
};

#endif /* StateMachine_H_ */

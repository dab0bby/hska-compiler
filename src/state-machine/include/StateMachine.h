/**
 * StateMachine.h
 */

#ifndef StateMachine_H_
#define StateMachine_H_

#include "State.h"

class StateMachine
{
public:
    StateMachine(vector<State*> states, int initialState);
    
    ~StateMachine();
    
    bool forward(char input);
    void reset();
    bool canForward() const;  
    bool isFinal() const;
    bool isInInitialState() const;
    int getCurrentToken() const;
    
private:
    int _initialState;
    int _currentState;
    vector<State*> _states;
};

#endif /* StateMachine_H_ */

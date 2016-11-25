//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_TRANSITION_H
#define HSKA_COMPILER_TRANSITION_H

class Condition;
class State;

// The base class for the different transitions. A Transition connects two states of a state machine.
class Transition
{
public:
    Transition(const Transition& other) = default;
    Transition(State* first, const State* second, const Condition& condition);
    ~Transition();

    State* getFirstState() const;
    State* getSecondState() const;
    Condition& getCondition() const;
    
    bool accepts(char input);

private:
    State* _first;
    State* _second;
    Condition& _condition;    
};

#endif //HSKA_COMPILER_TRANSITION_H

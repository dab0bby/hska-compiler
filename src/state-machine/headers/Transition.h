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
    Transition();
    Transition(State& first, const State& second, const Condition& condition);
    ~Transition();

    const State& getFirstState() const;
    const State& getSecondState() const;
    const Condition& getCondition() const;
    
    bool accepts(char input);

private:
    State& _first;
    const State& _second;
    const Condition& _condition;    
};

#endif //HSKA_COMPILER_TRANSITION_H

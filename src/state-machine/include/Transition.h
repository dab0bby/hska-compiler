//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_TRANSITION_H
#define HSKA_COMPILER_TRANSITION_H

class Condition;

// The base class for the different transitions. A Transition connects two states of a state machine.
class Transition
{
public:
#if defined (__clang__)
    Transition() {};
#endif
    Transition(const Transition& other);
    Transition(int target, const Condition* condition);
    ~Transition();

    //int getFirstState() const;
    int getTarget() const;
    Condition* getCondition() const;

    bool accepts(char input) const;

private:
   // int _first;
    int _target;
    Condition* _condition;
};

#endif //HSKA_COMPILER_TRANSITION_H

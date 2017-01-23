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
    Transition();
    Transition(const Transition& other);
    Transition(Transition&& other) noexcept;
    Transition(int target, const Condition* condition);
    ~Transition();    

    Transition& operator=(Transition&& other) noexcept;
    Transition& operator=(const Transition& other) noexcept;
    
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

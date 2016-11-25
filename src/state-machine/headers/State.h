//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_STATE_H
#define HSKA_COMPILER_STATE_H

#include "Transition.h"
#include "Condition.h"
#include "../../utils/header/vector.h"


class State
{
public:
    State();
    explicit State(bool isFinal);
    State(bool isFinal, int token);
    State(State* other, Condition& condition, bool isFinal);
    State(State* other, Condition& condition, bool isFinal, int token);

    ~State();

    // Connects this state with another state through an epsilon transition.
    Transition* connect(const State* other, const Condition& condition);

    vector<Transition*> getTransitions() const;

    bool isFinalState() const;
    void setFinalState(bool isFinal);
    void addTransition(const Transition* t);
    void removeTransition(const Transition* t);
    bool accepts(char input, State& next) const;
    bool hasTransitions() const;
    int token;

    static State empty;

private:
    vector<Transition*> _transitions;
    bool _isFinal;
};

#endif //HSKA_COMPILER_STATE_H

//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_STATE_H
#define HSKA_COMPILER_STATE_H

#include "Transition.h"
#include "Condition.h"
//#include "../../utils/include/vector.h"

#include "vector"

using namespace std;

class State
{
public:
    State();
    State(const State& other);
    explicit State(bool isFinal);
    State(bool isFinal, int token);
    State(int other, Condition* condition, bool isFinal);
    State(int other, Condition* condition, bool isFinal, int token);

    ~State();

    // Connects this state with another state through an epsilon transition.
    Transition* connect(int other, const Condition* condition);

    vector<Transition*> getTransitions() const;

    bool isFinalState() const;
    void setFinalState(bool isFinal);
    void addTransition(const Transition* t);
    void removeTransition(const Transition* t);
    bool accepts(char input, int& next) const;
    bool hasTransitions() const;
    int token;

    static State empty;

private:
    vector<Transition*> _transitions;
    bool _isFinal;
};

#endif //HSKA_COMPILER_STATE_H

#include "../headers/StateMachine.h"
#include <iostream>

using namespace std;

void testState()
{
    State a = State(), b = State(), c = State(), d = State();

    cout << "Testing 'State' class from project state-machine..." << endl;
    cout << "- connecting state 1 with state 2:    ";

    a.connect(b, 'a');

    bool check = a.getTransitions().size() == 1;
    check &= a.getTransitions()[0].getSecondState() == &b;
    check &= a.getTransitions()[0].getCondition() == 'g';

    cout << a.getTransitions()[0].print() << "    " << (check ? "OK" : "FAILED") << endl;

}

void testMachine()
{

}

int main ( int argc, char* argv[] )
{
    testState();
    testMachine();

    return 0;
}

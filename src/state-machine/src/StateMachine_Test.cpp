
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include "../include/Condition.h"
#include "../include/StateMachine.h"
#include "../include/TokenScanner.h"

using namespace std;

void testStateMachine()
{
    StateMachine sm(5, 0, new int[2]{ 4, 5 }, 2, Token::EQUAL);
    sm.setTransitions(0, new Transition[3]{
        Transition(1, new CharRangeCondition('a', 'z')),
        Transition(2, new CharRangeCondition('0', '9')),
        Transition(3, new CharRangeCondition('A', 'Z')) }, 3);

    sm.setTransitions(1, new Transition[1]{ Transition(4, new CharRangeCondition('0', '9')) }, 1);    
    sm.setTransitions(2, new Transition[1]{ Transition(5, new CharRangeCondition('a', 'z')) }, 1);
    sm.setTransitions(3, new Transition[1]{ Transition(5, new CharRangeCondition('0', '9')) }, 1);

    string test[] = { "a9", "8s", "C7", "79", "er", "aC"};
    
    bool ok = true;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < test[i].size(); j++)
        {
            char c = test[i][j];
            sm.process(c);
        }
            
        ok &= i < 3 ? sm.isInFinalState() : !sm.isInFinalState();    
        sm.reset();
    }

    cout << (ok ? "OK" : "FAIL");
}

void testTokenScanner(string text)
{
    TokenScanner scanner;
    for (int i = 0; i < text.size(); i++)    
        scanner.consume(text[i]);
    
    int line = 1;
    int offset = -1; 
    cout << "line " << line << ": ";
    
    for (auto t = scanner.getTokens(); t != nullptr; t = t->getNext())
    {
        cout << Token::getTokenName(t->token) << " (" << t->position - offset << ", " << t->size << "), ";
        
        if (t->token == Token::NEW_LINE)
        {
            offset = t->position;
            if (t->getNext() != nullptr)                
                cout << endl << "line " << ++line << ": ";
        }
    }
}

int main ( int argc, char* argv[] )
{
    auto path = "E:/Code/hska-compiler/test-files/scanner1.txt";
    
    ifstream file(path);
    stringstream fileContent;
    string testString;
    string str;

    while (getline(file, str))
        fileContent << str << "\n";

    // add some null terminator
    testString = fileContent.str() + '\0' + '\0' + '\0' + '\0';

    auto benchmarkStart = std::chrono::high_resolution_clock::now();

    cout << "testing state-machine with input file: " << path << endl << endl;

    testTokenScanner(testString);

    auto benchmarkEnd = std::chrono::high_resolution_clock::now();
    auto time = benchmarkEnd - benchmarkStart;

    cout << endl << endl << "finished in " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() / 1000.0 << "ms" << endl;

#ifdef _WIN32
    getchar();
#endif

    return 0;
}

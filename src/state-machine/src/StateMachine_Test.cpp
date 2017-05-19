
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include "../include/Condition.h"
#include "../include/StateMachine.h"
#include "../include/TokenScanner.h"
#include <experimental/filesystem>

#define BENCHMARK 0

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
    int line = 1;
    int offset = -1;

    TokenScanner scanner;
    for (int i = 0; i < text.size(); i++)
    {
        auto newTokens = scanner.consume(text[i]);

        if (newTokens)
        {
            auto token = scanner.getPendingTokens();
            while (token != nullptr)
            {
                if (token->token == Token::NEW_LINE)
                {
#if !BENCHMARK
                    cout << "line " << line << ", col " << token->begin - offset << ": " << Token::getTokenName(token->token) << " \"\\n\"" << endl;
#endif
                    line++;
                    offset = token->begin;
                }
                else
                {
#if !BENCHMARK
                    cout << "line " << line << ", col " << token->begin - offset << ": " << Token::getTokenName(token->token) << " \""
                        << text.substr(i - token->offset - token->size, token->size) << "\"" << endl;
#endif
                }

                token = token->getNext();
            }
        }
    }
}

void testWithKeywords(const string& path)
{
    TokenScanner tokenScanner;
        
    ifstream file(path);
    cout << path << endl << endl;
    stringstream ss;
    ss << "\t";

    for (string line; getline(file, line);)
    {
        if (line == "")
            continue;

        line += "\n";
        cout << "\t" << line;

        for (auto c : line)
        {
            tokenScanner.consume(c);
            auto pending = tokenScanner.getPendingTokens();

            while (pending != nullptr)
            {
                ss << Token(pending->token, 1, 1).getTypeStr() << " ";
                auto tmp = pending;
                pending = pending->getNext();
                delete tmp;
            }
        }
        ss << endl << "\t";
    }

    cout << endl << "interpreted as" << endl << endl << ss.str() << endl;
}

int main ( int argc, char* argv[] )
{
    string root = R"(F:\Code\hska-compiler\test-files)";
          
    for (auto& entry : experimental::filesystem::directory_iterator(root))
    {                
        if (!experimental::filesystem::is_regular_file(entry.status()) || experimental::filesystem::file_size(entry.path()) > 10000)
            continue;

        testWithKeywords(entry.path().string());
        cout << "######################################################" << endl << endl;
    }
    
#ifdef _WIN32
    system("Pause");
#endif

    return 0;
}

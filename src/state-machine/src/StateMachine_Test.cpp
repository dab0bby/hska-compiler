
#include "../include/LanguageParser.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>

using namespace std;

int main ( int argc, char* argv[] )
    auto path = "E:/Code/hska-compiler/test-files/scanner1.txt";
{
    LanguageParser lp;

    ifstream file(path);
    stringstream fileContent;
    string testString;
    string str;
    int token;

    while (getline(file, str))
        fileContent << str << "\n";

    // add some null terminator
    testString = fileContent.str() + '\0' + '\0' + '\0' + '\0';

    auto benchmarkStart = std::chrono::high_resolution_clock::now();

    cout << "testing state-machine with input file: " << path << endl << endl;

    for (int i = 0; i <= testString.size(); i++)
    {
        auto c = testString[i];

        bool parsed = lp.parse(c);

        token = lp.getToken();

    //    if (token != Token::DETECTING && token != Token::IGNORE)
            cout << Token::getTokenName(token) << ", ";

        if (token == Token::NEW_LINE)
            cout << endl << endl;

        if (!parsed)
        {
            lp.parse(c);
            token = lp.getToken();

            if (token != Token::DETECTING && token != Token::IGNORE)
                cout << Token::getTokenName(token) << ", ";

            if (token == Token::NEW_LINE)
                cout << endl << endl;
        }
    }

    auto benchmarkEnd = std::chrono::high_resolution_clock::now();
    auto time = benchmarkEnd - benchmarkStart;

    cout << endl << endl << "finished in " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "ms" << endl;

#ifdef _WIN32
    getchar();
#endif

    return 0;
}


#include "../headers/LanguageParser.h"
#include <iostream>

using namespace std;

int main ( int argc, char* argv[] )
{
    char* testText =
        "X: = 3 + 4;\n"
        ": *eine einfache Aufgabe !!* : ? y : = 7 = : = X : (X – 4);\n"
        "Z: = ((3 + 4 – 6);\n"
        "Resultat: = : X y %";

    char* tokenNames[] =
    {
        "NONE",

        "PLUS",
        "MINUS",
        "STAR",
        "COLON",
        "IF",
        "WHILE",
        "INTEGER",
        "IDENTIFIER",
        "SEMICOLON",
        "GREATER",
        "LESS",
        "EQUAL",
        "ASSIGN",
        "UNKNOWN_BULLSHIT_OPERATOR",
        "NOT",
        "AND",
        "BRACKET_OPEN",
        "BRACKET_CLOSE",
        "SQUARE_BRACKET_OPEN",
        "SQUARE_BRACKET_CLOSE",
        "CURLY_BRACKET_OPEN",
        "CURLY_BRACKET_CLOSE",
        "IGNORE",                     // white spaces and comments
        "ERROR",

        "STATE_TBD",      // special state (no valid token found right now)
        "STATE_FAILED"    // special state (no valid token can be found any further)        
    };
    
    cout << "Testing state-machine with input: " << endl << testText << endl << endl;

    LanguageParser lp;
    
    int i = 0;
    while(auto c = testText[i++] != '\0')
    {
        auto token = lp.parse(c);
        cout << i << " - " << c << " - " << tokenNames[token] << endl;
        
        if (token != Token::ERROR && lp.forecast(testText[i]) == token)
            continue;

        if (token == Token::ERROR || token != Token::NONE)
            lp.reset();
    }

    cout << "finished";
    getchar();
    return 0;
}

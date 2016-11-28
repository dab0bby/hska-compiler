
#include "../headers/LanguageParser.h"
#include <iostream>
#include "../../symbol-table/headers/Information.h"

using namespace std;


int main ( int argc, char* argv[] )
{
    char* testText =
        ":* Comment *: "
        ": * Invalid Comment *: "
        "X := 3 + 4; "
        "Z := 3 + 4; "
        "X = Z; "
        "Resultat := X : Z; "
        "WTF =:= IsThat; "
        "Y := X && Z";
        
    cout << "Testing state-machine with input: " << endl << testText << endl << endl;

    LanguageParser lp;
    
    int i = 0;
    char c;
    int lastToken = Token::NONE;

    while((c = testText[i++]) != '\0')
    {
        auto token = lp.parse(c);
        bool suppressCout = false;

        if (lp.needsReset())
        {
            lp.reset();
            if ((suppressCout = token == Token::ERROR && lastToken != Token::ERROR))
                i--;
        }

        if (!suppressCout)
            cout << i << " - " << c << " - " << Token::getTokenName(token) << endl;   

        lastToken = token;
    }

    cout << "finished";
    getchar();
    return 0;
}

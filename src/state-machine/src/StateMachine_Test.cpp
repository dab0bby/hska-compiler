
#include "../include/LanguageParser.h"
#include <iostream>
#include <string>

using namespace std;


int main ( int argc, char* argv[] )
{
    string testText =
        ":* Comment *:"
        ": * Invalid Comment *: "
        "X := 3 + 4; "
        "Z := 3 + 4; "
        "X = Z; "
        "Resultat := X : Z; "
        "WTF =:= IsThat; "
        "Y := X && Z if If IF iff "
        "while " // WHILE
        "WhiLE? " // IDENTIFIER ERROR
        "whileif " // IDENTIFIER
        "? % & " // ERROR ERROR ERROR
        "Test&vier"; // IDENTIFIER ERROR IDENTIFIER

    cout << "Testing state-machine with input: " << endl << testText << endl << endl;

    LanguageParser lp;

    int i = 0;
    char c;
    int start = 0;
    int size = 0;

    do
    {
        auto valid = true;
        c = testText[i];

        if (c == '\0')
            lp.finalize();
        else
            valid = lp.parse(c);

        if (valid)
        {
            size++;
            auto token = lp.getToken();

            if (lp.detectionCompleted())
            {
                cout << "found " << Token::getTokenName(token) << " at " << start << " for " << size << " \"" << testText.substr(start, size) << "\"" << endl;
                start = i;
                size = 0;
            }
            else if (token == Token::IGNORE)
            {
                start = i;
                size = 0;
            }
        }
        else
        {
            cout << "error at " << i << " \"" << testText[i] << "\"" << endl;
        }

        i++;
    } while (c != '\0');

    cout << "finished";
    getchar();
    return 0;
}

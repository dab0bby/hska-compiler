//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_LANGUAGEPARSER_H
#define HSKA_COMPILER_LANGUAGEPARSER_H

#include "StateMachine.h"
#include "../../scanner/include/Token.h"
#include "vector"

using namespace std;

// The base class for the different transitions. A Transition connects two states of a state machine.
class LanguageParser
{
public:
    LanguageParser();
    ~LanguageParser();

    void reset();

    /**
     * \brief Tries to parse the given char. If this function returns false, an error has occured and it has to be called with the same parameter again. The getToken() function
     * will then return an ERROR token one iteration after the char that causes the error. 
     * Note: if this function returns true, but getToken() returns an ERROR token, a second call of this function is not needed because the ERROR can also include following chars.
     */
    bool parse(char input);
    
    /**
     * \brief Gets the token that belongs to the previous parsed character. This function is always one iteration behind the parse(char input) function. 
     */
    Token::TokenType getToken() const;

private:    

    bool _createError();

    StateMachine* _sm;
    vector<State*> _states;    
    AnyOfCondition* _space = new AnyOfCondition(" \t");
    AnyOfCondition* _newline = new AnyOfCondition("\n\r");
    AnyOfCondition* _whitespace = new AnyOfCondition(" \t\n\r");
    CharRangeCondition* _digit = new CharRangeCondition('0', '9');
    CharRangeCondition* _lowerCase = new CharRangeCondition('a', 'z');
    CharRangeCondition* _upperCase = new CharRangeCondition('A', 'Z');
    OrCondition* _letter = new OrCondition(_lowerCase, _upperCase);
    OrCondition* _alphanumerical = new OrCondition(_letter, _digit);

    bool _didForward = false;
    int _lastToken = Token::DETECTING;
    int _currentToken = Token::DETECTING;
    int _setToken = Token::IGNORE;
    int _detectedToken = Token::DETECTING;
};

#endif //HSKA_COMPILER_LANGUAGEPARSER_H

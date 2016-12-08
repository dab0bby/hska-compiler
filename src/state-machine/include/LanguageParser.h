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
    bool parse(char input);
    void finalize();
    bool detectionCompleted() const;
    Token::TokenType getToken() const;

private:    

    bool _createError();

    StateMachine* _sm;
    vector<State*> _states;

    StringCondition* _whitespace = new StringCondition(" \t\n\r");
    CharRangeCondition* _digit = new CharRangeCondition('0', '9');
    CharRangeCondition* _lowerCase = new CharRangeCondition('a', 'z');
    CharRangeCondition* _upperCase = new CharRangeCondition('A', 'Z');
    MultiCondition* _letter = new MultiCondition(_lowerCase, _upperCase);

    bool _didForward = false;
    bool _smDidReset = false;
    bool _smError = false;
    int _lastToken = Token::NONE;
    int _currentToken = Token::NONE;
    int _detectedToken = Token::NONE;
};

#endif //HSKA_COMPILER_LANGUAGEPARSER_H

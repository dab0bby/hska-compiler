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
    Token::TokenType parse(char input);
    Token::TokenType forecast(char input) const;
    bool needsReset() const;

private:    
    StateMachine* _sm;
    vector<State*> _states;

    StringCondition* _whitespace = new StringCondition(" \t\n\r");
    CharRangeCondition* _digit = new CharRangeCondition('0', '9');
    CharRangeCondition* _lowerCase = new CharRangeCondition('a', 'z');
    CharRangeCondition* _upperCase = new CharRangeCondition('A', 'Z');
    MultiCondition* _letter = new MultiCondition(_lowerCase, _upperCase);

    bool _didForward = false;
};

#endif //HSKA_COMPILER_LANGUAGEPARSER_H

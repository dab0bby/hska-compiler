//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_LANGUAGEPARSER_H
#define HSKA_COMPILER_LANGUAGEPARSER_H

#include "StateMachine.h"
#include "../../scanner/include/Token.h"


// The base class for the different transitions. A Transition connects two states of a state machine.
class LanguageParser
{
public:
    LanguageParser();
    ~LanguageParser();

    void reset();
    Token::TokenType parse(char input) const;
    Token::TokenType forecast(char input) const;


private:    
    StateMachine* _sm;
};

#endif //HSKA_COMPILER_LANGUAGEPARSER_H

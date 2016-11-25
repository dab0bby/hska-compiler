//
// Created by timo on 05.11.15.
//

#include "../headers/LanguageParser.h"

LanguageParser::LanguageParser()
{
    auto whitespace = StringCondition(" \t\n\r");
    auto digit = StringCondition("0123456789");
    auto lowerCase = CharRangeCondition('a', 'z');
    auto upperCase = CharRangeCondition('A', 'Z');
    auto letter = MultiCondition(&lowerCase, &upperCase);

    vector<State*> states;
    /* 00 */ states.add(new State(true, Token::IGNORE));
    /* 01 */ states.add(new State(false, Token::COLON));
    /* 02 */ states.add(new State(false, Token::IGNORE));
    /* 03 */ states.add(new State(false, Token::NONE));
    /* 04 */ states.add(new State(true, Token::IGNORE));
    /* 05 */ states.add(new State(true, Token::ASSIGN));
    /* 06 */ states.add(new State(true, Token::PLUS));
    /* 07 */ states.add(new State(true, Token::MINUS));
    /* 08 */ states.add(new State(true, Token::EQUAL));
    /* 09 */ states.add(new State(false, Token::NONE));
    /* 10 */ states.add(new State(true, Token::UNKNOWN_BULLSHIT_OPERATOR));
    /* 11 */ states.add(new State(false, Token::NONE));
    /* 12 */ states.add(new State(true, Token::AND));
    /* 13 */ states.add(new State(true, Token::INTEGER));
    /* 14 */ states.add(new State(true, Token::IDENTIFIER));
    /* 15 */ states.add(new State(true, Token::STAR));
    /* 16 */ states.add(new State(true, Token::LESS));
    /* 17 */ states.add(new State(true, Token::GREATER));
    /* 18 */ states.add(new State(true, Token::NOT));
    /* 19 */ states.add(new State(true, Token::SEMICOLON));
    /* 20 */ states.add(new State(true, Token::BRACKET_OPEN));
    /* 21 */ states.add(new State(true, Token::BRACKET_CLOSE));
    /* 22 */ states.add(new State(true, Token::CURLY_BRACKET_OPEN));
    /* 23 */ states.add(new State(true, Token::CURLY_BRACKET_CLOSE));
    /* 24 */ states.add(new State(true, Token::SQUARE_BRACKET_OPEN));
    /* 25 */ states.add(new State(true, Token::SQUARE_BRACKET_CLOSE));

    
    states[0]->connect(states[0], whitespace);
    states[0]->connect(states[1], CharCondition(':'));
    states[0]->connect(states[6], CharCondition('+'));
    states[0]->connect(states[7], CharCondition('-'));
    states[0]->connect(states[8], CharCondition('='));
    states[0]->connect(states[11], CharCondition('&'));
    states[0]->connect(states[13], digit);
    states[0]->connect(states[14], letter);
    states[0]->connect(states[15], CharCondition('*'));
    states[0]->connect(states[16], CharCondition('<'));
    states[0]->connect(states[17], CharCondition('>'));
    states[0]->connect(states[18], CharCondition('!'));
    states[0]->connect(states[19], CharCondition(';'));
    states[0]->connect(states[20], CharCondition('('));
    states[0]->connect(states[21], CharCondition(')'));
    states[0]->connect(states[22], CharCondition('{'));
    states[0]->connect(states[23], CharCondition('}'));
    states[0]->connect(states[24], CharCondition('['));
    states[0]->connect(states[25], CharCondition(']'));

    states[1]->connect(states[2], CharCondition('*'));
    states[1]->connect(states[5], CharCondition('='));
  
    states[2]->connect(states[2], NotCondition(CharCondition('*')));
    states[2]->connect(states[3], CharCondition('*'));

    states[3]->connect(states[3], CharCondition('*'));
    states[3]->connect(states[4], CharCondition(':'));
    states[3]->connect(states[2], NotCondition(StringCondition("*:")));

    states[8]->connect(states[9], CharCondition(':'));

    states[9]->connect(states[10], CharCondition('='));

    states[11]->connect(states[12], CharCondition('&'));

    states[13]->connect(states[13], digit);
    
    states[14]->connect(states[14], MultiCondition(&digit, &letter));
    
    _sm = new StateMachine(*states[0]);
}

LanguageParser::~LanguageParser()
{
    for (int i = 0; i < states.size(); i++)
        delete states[i];

    delete _sm;
}


void LanguageParser::reset()
{
    _sm->reset();
}

Token::TokenType LanguageParser::parse(char input) const
{
    if (_sm->forward(input))    
        return static_cast<Token::TokenType>(_sm->getCurrentToken());    
    
    return Token::ERROR;
}

Token::TokenType LanguageParser::forecast(char input) const
{
    int token;
    if (_sm->forecast(input, token))    
        return static_cast<Token::TokenType>(token);    

    return Token::ERROR;
}

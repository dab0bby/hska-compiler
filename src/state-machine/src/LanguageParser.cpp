//
// Created by timo on 05.11.15.
//

#include "../include/LanguageParser.h"


LanguageParser::LanguageParser()
{
    /* 00 */ _states.push_back(new State(true, Token::IGNORE));
    /* 01 */ _states.push_back(new State(false, Token::COLON));
    /* 02 */ _states.push_back(new State(false, Token::IGNORE));
    /* 03 */ _states.push_back(new State(false, Token::IGNORE));
    /* 04 */ _states.push_back(new State(true, Token::IGNORE));
    /* 05 */ _states.push_back(new State(true, Token::ASSIGN));
    /* 06 */ _states.push_back(new State(true, Token::PLUS));
    /* 07 */ _states.push_back(new State(true, Token::MINUS));
    /* 08 */ _states.push_back(new State(true, Token::EQUAL));
    /* 09 */ _states.push_back(new State(false, Token::NONE));
    /* 10 */ _states.push_back(new State(true, Token::UNKNOWN_BULLSHIT_OPERATOR));
    /* 11 */ _states.push_back(new State(false, Token::NONE));
    /* 12 */ _states.push_back(new State(true, Token::AND));
    /* 13 */ _states.push_back(new State(true, Token::INTEGER));
    /* 14 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 15 */ _states.push_back(new State(true, Token::STAR));
    /* 16 */ _states.push_back(new State(true, Token::LESS));
    /* 17 */ _states.push_back(new State(true, Token::GREATER));
    /* 18 */ _states.push_back(new State(true, Token::NOT));
    /* 19 */ _states.push_back(new State(true, Token::SEMICOLON));
    /* 20 */ _states.push_back(new State(true, Token::BRACKET_OPEN));
    /* 21 */ _states.push_back(new State(true, Token::BRACKET_CLOSE));
    /* 22 */ _states.push_back(new State(true, Token::CURLY_BRACKET_OPEN));
    /* 23 */ _states.push_back(new State(true, Token::CURLY_BRACKET_CLOSE));
    /* 24 */ _states.push_back(new State(true, Token::SQUARE_BRACKET_OPEN));
    /* 25 */ _states.push_back(new State(true, Token::SQUARE_BRACKET_CLOSE));

    _states[0]->connect(0, _whitespace);
    _states[0]->connect(1, new CharCondition(':'));
    _states[0]->connect(6, new CharCondition('+'));
    _states[0]->connect(7, new CharCondition('-'));
    _states[0]->connect(8, new CharCondition('='));
    _states[0]->connect(11, new CharCondition('&'));
    _states[0]->connect(13, _digit);
    _states[0]->connect(14, _letter);
    _states[0]->connect(15, new CharCondition('*'));
    _states[0]->connect(16, new CharCondition('<'));
    _states[0]->connect(17, new CharCondition('>'));
    _states[0]->connect(18, new CharCondition('!'));
    _states[0]->connect(19, new CharCondition(';'));
    _states[0]->connect(20, new CharCondition('('));
    _states[0]->connect(21, new CharCondition(')'));
    _states[0]->connect(22, new CharCondition('{'));
    _states[0]->connect(23, new CharCondition('}'));
    _states[0]->connect(24, new CharCondition('['));
    _states[0]->connect(25, new CharCondition(']'));

    _states[1]->connect(2, new CharCondition('*'));
    _states[1]->connect(5, new CharCondition('='));

    _states[2]->connect(2, new NotCondition(new CharCondition('*')));
    _states[2]->connect(3, new CharCondition('*'));

    _states[3]->connect(0, new CharCondition(':'));
    _states[3]->connect(3, new CharCondition('*'));
    _states[3]->connect(2, new NotCondition(new StringCondition("*:")));

    _states[8]->connect(9, new CharCondition(':'));

    _states[9]->connect(10, new CharCondition('='));

    _states[11]->connect(12, new CharCondition('&'));

    _states[13]->connect(13, _digit);

    _states[14]->connect(14, new MultiCondition(_digit, _letter));

    _sm = new StateMachine(_states, 0);
}

LanguageParser::~LanguageParser()
{
    for (int i = 0; i < _states.size(); i++)    
        delete _states[i];    

    delete _sm;
}


void LanguageParser::reset()
{
    _sm->reset();
}

bool LanguageParser::parse(char input)
{
    _smError = false;
    _smDidReset = false;
    _lastToken = _currentToken;
    _detectedToken = Token::NONE;

    _didForward = _sm->forward(input);

    // sm couldn't proceed
    if (!_didForward)
    {
        _smDidReset = true;
        _detectedToken = _lastToken;

        // sm is already in initial state -> char unaccaptable
        if (_sm->isInInitialState())
            return _createError();
        
        // reset sm and try again
        _sm->reset();
        _didForward = _sm->forward(input);

        // sm couldn't proceed again -> char unaccaptable
        if (!_didForward)
            return _createError();
    }
        
    _currentToken = _sm->getCurrentToken();
    
    if (_lastToken == Token::IGNORE)
        _detectedToken = _lastToken;

    return true;
}

void LanguageParser::finalize()
{
    parse(';');
}

bool LanguageParser::detectionCompleted() const
{
    return !_smError && _smDidReset;
}

Token::TokenType LanguageParser::getToken() const
{
    return static_cast<Token::TokenType>(_detectedToken);
}

bool LanguageParser::_createError()
{
    _smError = true;
    _currentToken = Token::NONE;
    _detectedToken = Token::ERROR;
    return false;
}



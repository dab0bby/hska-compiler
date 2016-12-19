//
// Created by timo on 05.11.15.
//

#include "../include/LanguageParser.h"


LanguageParser::LanguageParser()
{
    /* 00 */ _states.push_back(new State(true, Token::IGNORE));
    /* 01 */ _states.push_back(new State(true, Token::COLON));
    /* 02 */ _states.push_back(new State(false, Token::IGNORE));
    /* 03 */ _states.push_back(new State(false, Token::IGNORE));
    /* 04 */ _states.push_back(new State(true, Token::IGNORE));
    /* 05 */ _states.push_back(new State(true, Token::ASSIGN));
    /* 06 */ _states.push_back(new State(true, Token::PLUS));
    /* 07 */ _states.push_back(new State(true, Token::MINUS));
    /* 08 */ _states.push_back(new State(true, Token::EQUAL));
    /* 09 */ _states.push_back(new State(false, Token::DETECTING));
    /* 10 */ _states.push_back(new State(true, Token::UNKNOWN_BULLSHIT_OPERATOR));
    /* 11 */ _states.push_back(new State(false, Token::DETECTING));
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
    /* 26 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 27 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 28 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 29 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 30 */ _states.push_back(new State(true, Token::WHILE));
    /* 31 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 32 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 33 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 34 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 35 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 36 */ _states.push_back(new State(true, Token::IDENTIFIER));
    /* 37 */ _states.push_back(new State(true, Token::IF));
    /* 38 */ _states.push_back(new State(true, Token::EOF_TOKEN));
    /* 39 */ _states.push_back(new State(true, Token::NEW_LINE));
    /* 40 */ _states.push_back(new State(true, Token::NEW_LINE));
    /* 41 */ _states.push_back(new State(true, Token::ERROR));   
    
    

    _states[0]->connect(0, _space);
    _states[0]->connect(1, new CharCondition(':'));
    _states[0]->connect(6, new CharCondition('+'));
    _states[0]->connect(7, new CharCondition('-'));
    _states[0]->connect(8, new CharCondition('='));
    _states[0]->connect(11, new CharCondition('&'));
    _states[0]->connect(13, _digit);
    _states[0]->connect(14, new AndCondition(_letter, new NotCondition(new AnyOfCondition("WwIi"))));
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
    _states[0]->connect(26, new CharCondition('W'));
    _states[0]->connect(31, new CharCondition('w'));
    _states[0]->connect(35, new CharCondition('I'));
    _states[0]->connect(36, new CharCondition('i'));
    _states[0]->connect(38, new CharCondition('\0'));
    _states[0]->connect(39, _newline);

    _states[1]->connect(2, new CharCondition('*'));
    _states[1]->connect(5, new CharCondition('='));

    _states[2]->connect(40, _newline);
    _states[2]->connect(2, new NotCondition(new OrCondition(new CharCondition('*'), _newline)));
    _states[2]->connect(3, new CharCondition('*'));

    _states[3]->connect(0, new CharCondition(':'));
    _states[3]->connect(3, new CharCondition('*'));
    _states[3]->connect(2, new NotCondition(new AnyOfCondition("*:")));

    _states[8]->connect(9, new CharCondition(':'));

    _states[9]->connect(10, new CharCondition('='));

    _states[11]->connect(12, new CharCondition('&'));

    _states[13]->connect(13, _digit);
    _states[13]->connect(41, _letter);

    _states[14]->connect(14, _alphanumerical);
    
    _states[26]->connect(27, new CharCondition('H'));
    _states[26]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('H'))));

    _states[27]->connect(28, new CharCondition('I'));
    _states[27]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('I'))));

    _states[28]->connect(29, new CharCondition('L'));
    _states[28]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('L'))));

    _states[29]->connect(30, new CharCondition('E'));
    _states[29]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('E'))));

    _states[30]->connect(14, _alphanumerical);
    
    _states[31]->connect(32, new CharCondition('h'));
    _states[31]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('h'))));

    _states[32]->connect(33, new CharCondition('i'));
    _states[32]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('i'))));

    _states[33]->connect(34, new CharCondition('l'));
    _states[33]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('l'))));

    _states[34]->connect(30, new CharCondition('e'));
    _states[34]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('e'))));


    _states[35]->connect(37, new CharCondition('F'));
    _states[35]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('F'))));

    _states[36]->connect(37, new CharCondition('f'));
    _states[36]->connect(14, new AndCondition(_alphanumerical, new NotCondition(new CharCondition('f'))));
    
    _states[37]->connect(14, _alphanumerical);    
    
    _states[38]->connect(38, new TrueCondition());   
    
    _states[40]->connect(40, _newline);      
    _states[40]->connect(2, new NotCondition(_newline));      

    _states[41]->connect(41, _alphanumerical);      

    _sm = new StateMachine(_states, 0);
}

LanguageParser::~LanguageParser()
{
    delete _sm;
}


void LanguageParser::reset()
{
    _sm->reset();
}

bool LanguageParser::parse(char input)
{    
    _lastToken = _currentToken;
    _detectedToken = _setToken;
    _setToken = Token::DETECTING;

    _didForward = _sm->forward(input);

    // sm couldn't proceed
    if (!_didForward)
    {
        _detectedToken = _lastToken;

        // sm is already in initial state -> char unaccaptable
        if (_sm->isInInitialState() || !_sm->isFinal())
            return _createError();
        
        // reset sm and try again
        _sm->reset();
        _didForward = _sm->forward(input);

        // sm couldn't proceed again -> char unaccaptable
        if (!_didForward)
            return _createError();
    }
        
    _currentToken = _sm->getCurrentToken();
    
    if (_currentToken == Token::IGNORE || _currentToken == Token::NEW_LINE || _currentToken == Token::EOF_TOKEN || _currentToken == Token::ERROR)    
        _setToken = _currentToken;
        
    return true;
}

Token::TokenType LanguageParser::getToken() const
{
    return static_cast<Token::TokenType>(_detectedToken);
}

bool LanguageParser::_createError()
{
    _sm->reset();
    _currentToken = Token::DETECTING;
    _setToken = Token::ERROR;
    return false;
}



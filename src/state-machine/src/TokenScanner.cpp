#include "../include/TokenScanner.h"
#include "../include/Condition.h"
#include <iostream>
#include <string>

TokenScanner::TokenScanner()
{
    _sms = new StateMachine*[SM_CNT];

    _sms[1] = StateMachine::createAtomic(Token::PLUS, new CharCondition('+'));
    _sms[2] = StateMachine::createAtomic(Token::MINUS, new CharCondition('-'));
    _sms[3] = StateMachine::createAtomic(Token::STAR, new CharCondition('*'));
    _sms[4] = StateMachine::createAtomic(Token::COLON, new CharCondition(':'));
    _sms[7] = StateMachine::createAtomic(Token::SEMICOLON, new CharCondition(';'));
    _sms[8] = StateMachine::createAtomic(Token::GREATER, new CharCondition('>'));
    _sms[9] = StateMachine::createAtomic(Token::LESS, new CharCondition('<'));
    _sms[10] = StateMachine::createAtomic(Token::EQUAL, new CharCondition('='));
    _sms[13] = StateMachine::createAtomic(Token::NOT, new CharCondition('!'));
    _sms[15] = StateMachine::createAtomic(Token::BRACKET_OPEN, new CharCondition('('));
    _sms[16] = StateMachine::createAtomic(Token::BRACKET_CLOSE, new CharCondition(')'));
    _sms[17] = StateMachine::createAtomic(Token::SQUARE_BRACKET_OPEN, new CharCondition('['));
    _sms[18] = StateMachine::createAtomic(Token::SQUARE_BRACKET_CLOSE, new CharCondition(']'));
    _sms[19] = StateMachine::createAtomic(Token::CURLY_BRACKET_OPEN, new CharCondition('{'));
    _sms[20] = StateMachine::createAtomic(Token::CURLY_BRACKET_CLOSE, new CharCondition('}'));

    // state machine for whitespaces and comments
    _sms[SM_IGN] = new StateMachine(4, 0, new int[3]{ 0,2,3 }, 3, Token::IGNORE);
    _sms[SM_IGN]->setTransitions(0, new Transition[2]{
        Transition(0, Condition::createWhitespace()),
        Transition(1, new CharCondition(':')) }, 2);
    _sms[SM_IGN]->setTransitions(1, new Transition[1]{
        Transition(2, new CharCondition('*')) }, 1);
    _sms[SM_IGN]->setTransitions(2, new Transition[2]{
        Transition(3, new CharCondition('*')),
        Transition(2, new NotCondition(new CharCondition('*'))) }, 2);
    _sms[SM_IGN]->setTransitions(3, new Transition[3]{
        Transition(3, new CharCondition('*')),
        Transition(0, new CharCondition(':')),
        Transition(2, new NotCondition(new OrCondition(new CharCondition('*'), new CharCondition(':')))) }, 3);

    // state machine for integers
    _sms[5] = StateMachine::createAtomic(Token::INTEGER);
    _sms[5]->setTransitions(0, new Transition[1]{ Transition(1, Condition::createDigit()) }, 1);
    _sms[5]->setTransitions(1, new Transition[1]{ Transition(1, Condition::createDigit()) }, 1);

    // state machine for identifier
    _sms[6] = StateMachine::createAtomic(Token::IDENTIFIER);
    _sms[6]->setTransitions(0, new Transition[1]{ Transition(1, Condition::createAlphabet()) }, 1);
    _sms[6]->setTransitions(1, new Transition[1]{ Transition(1, Condition::createAlphanumerical()) }, 1);

    _sms[11] = new StateMachine(3, 0, 2, Token::ASSIGN);
    _sms[11]->setTransitions(0, Transition(1, new CharCondition(':')));
    _sms[11]->setTransitions(1, Transition(2, new CharCondition('=')));

    _sms[12] = new StateMachine(4, 0, 3, Token::EXPRESSION_EQUAL);
    _sms[12]->setTransitions(0, Transition(1, new CharCondition('=')));
    _sms[12]->setTransitions(1, Transition(2, new CharCondition(':')));
    _sms[12]->setTransitions(2, Transition(3, new CharCondition('=')));

    _sms[14] = new StateMachine(3, 0, 2, Token::AND);
    _sms[14]->setTransitions(0, Transition(1, new CharCondition('&')));
    _sms[14]->setTransitions(1, Transition(2, new CharCondition('&')));

    // state machine for line breaks
    _sms[SM_LF] = StateMachine::createAtomic(Token::NEW_LINE, Condition::createLinefeed());
}

TokenScanner::~TokenScanner()
{
    for (int i = 0; i < SM_CNT; i++)
        delete _sms[i];

    delete[] _sms;
}

void TokenScanner::consume(char c)
{   
    if (c == '\n')
        std::cout << _position << ": consuming '\\n' ";
    else
        std::cout << _position << ": consuming '" << c << "' ";

    bool anyProgress = false;
    bool skip = false;

    for (int i = 0; i < SM_CNT; i++)
    {
        if (skip && i != SM_LF)
        {
            _sms[i]->reset(_position + 1);
            continue;
        }

        auto valid = _sms[i]->process(c);
                
        if (valid)
        {
            if (_sms[i]->isInFinalState())
                _appendToken(new TokenPosition(_sms[i]->getToken(), _sms[i]->startPosition, _sms[i]->processed));            
        }
        else 
        {
            _sms[i]->reset(_position);            
            valid = _sms[i]->process(c);

            if (valid)
            {
                if (_sms[i]->isInFinalState())
                    _appendToken(new TokenPosition(_sms[i]->getToken(), _sms[i]->startPosition, _sms[i]->processed));
            }
            else
            {
                _sms[i]->reset(_position + 1);
            }
        }

        if (valid && i == SM_IGN && _sms[SM_IGN]->isInFinalState())
            skip = true;

        anyProgress |= valid;
    }

    if (!anyProgress)
        _appendToken(new TokenPosition(Token::ERROR, _position, 1));

    std::cout << std::endl;
    _position++;
}

void TokenScanner::reset()
{
    for (int i = 0; i < SM_CNT; i++)
        _sms[i]->reset(_position);

    TokenPosition::deleteAllNext(_startToken);
    delete _startToken;
    _startToken = nullptr;
}

int TokenScanner::getPosition() const
{
    return _position;
}

void TokenScanner::setPosition(int position)
{
    _position = position;
}

void TokenScanner::setFilter(int filter)
{
    _filter = filter;
}

int TokenScanner::getFilter() const
{
    return _filter;
}

TokenPosition* TokenScanner::getTokens() const
{
    return _startToken;
}

void TokenScanner::_appendToken(TokenPosition* token)
{
    if (Token::getTokenName(token->token) == "<UNKNOWN>")
    {
        std::cout << "<DELETE>";
    }

    if (_lastTokenEnd < token->position)    
        _appendToken(new TokenPosition(Token::ERROR, _lastTokenEnd, token->position - _lastTokenEnd));
    

    if (token->position + token->size > _lastTokenEnd)
        _lastTokenEnd = token->position + token->size;


    bool accept = _filter & token->token;
    
    // initial call
    if (_lastToken == nullptr)
    {
        _startToken = token;
        _lastToken = _startToken;
        return;
    }

    // last token is larger then the new token
    if (_lastToken->position < token->position && _lastToken->position + _lastToken->size > token->position + token->size)
        return;

    auto t = _lastToken;

    // delete Tokens that intersect with the new token (in terms of positioning)
    while (t != nullptr)
    {
        auto end = t->position + t->size;
        if (end <= token->position)
            break;
        
        auto tmp = t->getPrevious();

        if (tmp == token)
        {
            std::cout << "<DELETE>";
        }
        delete t;
        t = tmp;
    } 
        
    if (!accept)
    {
        if (t != nullptr)
            t->setNext(nullptr);

        if (Token::getTokenName(token->token) == "<UNKNOWN>")
        {
            std::cout << "<DELETE>";
        }

        delete token;
        token = nullptr;
        return;
    }

    std::cout << "appending token: " << Token::getTokenName(token->token) << " (" << token->position << ", " << token->size << ") ";
    
    if (t != nullptr)
        t->setNext(token);
    else
        _startToken = token;
    
    _lastToken = token;
}

void TokenScanner::_findPosition(TokenPosition* token, TokenPosition*& previous, int& inbetween, TokenPosition*& next) const

void TokenScanner::_printTokens(TokenPosition* token) const
{    
    auto t = token;
    for (; t )
}


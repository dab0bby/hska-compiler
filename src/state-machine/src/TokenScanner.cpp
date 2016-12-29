#include "../include/TokenScanner.h"
#include "../include/Condition.h"

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
    _sms[22] = StateMachine::createAtomic(Token::EOF_TOKEN, new CharCondition('\0'));

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
    _sms[SM_INT] = StateMachine::createAtomic(Token::INTEGER);
    _sms[SM_INT]->setTransitions(0, new Transition[1]{ Transition(1, Condition::createDigit()) }, 1);
    _sms[SM_INT]->setTransitions(1, new Transition[1]{ Transition(1, Condition::createDigit()) }, 1);

    // state machine for identifier
    _sms[SM_IDFR] = StateMachine::createAtomic(Token::IDENTIFIER);
    _sms[SM_IDFR]->setTransitions(0, new Transition[1]{ Transition(1, Condition::createAlphabet()) }, 1);
    _sms[SM_IDFR]->setTransitions(1, new Transition[1]{ Transition(1, Condition::createAlphanumerical()) }, 1);

    // state machine for :=
    _sms[11] = new StateMachine(3, 0, 2, Token::ASSIGN);
    _sms[11]->setTransitions(0, Transition(1, new CharCondition(':')));
    _sms[11]->setTransitions(1, Transition(2, new CharCondition('=')));

    // state machine for =:=
    _sms[12] = new StateMachine(4, 0, 3, Token::EXPRESSION_EQUAL);
    _sms[12]->setTransitions(0, Transition(1, new CharCondition('=')));
    _sms[12]->setTransitions(1, Transition(2, new CharCondition(':')));
    _sms[12]->setTransitions(2, Transition(3, new CharCondition('=')));

    // state machine for &&
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

bool TokenScanner::consume(char c)
{
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

    _mergePendingToken(skip);

    _position++;

    return _startToken != nullptr;
}

void TokenScanner::reset()
{
    for (int i = 0; i < SM_CNT; i++)
        _sms[i]->reset(_position);

    TokenPosition::deleteAllNext(_startToken);
    delete _startToken;
    _startToken = nullptr;
}

int TokenScanner::getConsumeCount() const
{
    return _position;
}

void TokenScanner::setFilter(int filter)
{
    _filter = filter;
}

int TokenScanner::getFilter() const
{
    return _filter;
}

TokenPosition* TokenScanner::getPendingTokens()
{
    if (_startToken == nullptr)
        return nullptr;

    auto tmp = _startToken;
    _applyOffset(tmp, _position - 1);
    _startToken = nullptr;
    _lastToken = nullptr;
    return tmp;
}

void TokenScanner::_appendToken(TokenPosition* token)
{
    // make an error if unresolved spaces are between tokens
    if (_lastTokenEnd < token->begin)
        _appendToken(new TokenPosition(Token::ERROR, _lastTokenEnd, token->begin - _lastTokenEnd));

    bool accept = _filter & token->token;

    // initial call
    if (_pendingToken == nullptr)
    {
        if (accept)
            _pendingToken = token;

        _lastTokenEnd = token->begin + token->size;
        return;
    }

    // last token is larger then the new token or the new token begins before the last token
    if ((_pendingToken->begin < token->begin && _pendingToken->begin + _pendingToken->size > token->begin + token->size) || (token->begin < _lastOutputEnd))
        return;

    // move end position of last token
    if (token->begin + token->size > _lastTokenEnd)
        _lastTokenEnd = token->begin + token->size;

    auto t = _pendingToken;

    // delete Tokens that intersect with the new token (in terms of positioning)
    while (t != nullptr)
    {
        auto end = t->begin + t->size;
        if (end <= token->begin)
            break;

        auto tmp = t->getPrevious();

        delete t;
        t = tmp;
    }

    if (!accept)
    {
        if (t != nullptr)
            t->setNext(nullptr);

        _pendingToken = t;
        delete token;
        return;
    }

    if (t != nullptr)
        t->setNext(token);

    _pendingToken = token;
}

void TokenScanner::_mergePendingToken(bool skippedLast)
{
    if (_pendingToken == nullptr)
        return;

    auto first = _pendingToken;
    TokenPosition::jumpToFirst(first);

    // some types got filtered out, therefore the type has changed
    if (skippedLast)
    {
        if (_lastToken == nullptr)
        {
            _startToken = first;
            _lastToken = _pendingToken;
        }
        else
        {
            _lastToken->setNext(first);
            _lastToken = _pendingToken;
        }

        _pendingToken = nullptr;
        _lastOutputEnd = _lastToken->begin + _lastToken->size;
        return;
    }

    // : := and =:=
    if (_pendingToken->token == Token::COLON || _pendingToken->token == Token::EQUAL || (_pendingToken->token == Token::AND && _pendingToken->size < 2))
        return;

    // pending Identifier and Integers
    if ((_pendingToken->token == Token::IDENTIFIER && _sms[SM_IDFR]->isInFinalState()) ||
        (_pendingToken->token == Token::INTEGER && _sms[SM_INT]->isInFinalState()))
        return;

    // Identifier and Intergers
    if ((first->token == Token::IDENTIFIER && _sms[SM_IDFR]->isInInitialState()) ||
        (first->token == Token::INTEGER && _sms[SM_INT]->isInInitialState()))
    {
        auto end = _pendingToken->token & _filter ? _pendingToken : _pendingToken->getPrevious();

        if (_lastToken == nullptr)
        {
            _startToken = first;
            _lastToken = end;
        }
        else
        {
            _lastToken->setNext(first);
            _lastToken = end;
        }

        _pendingToken = end->getNext();

        if (_pendingToken != nullptr)
            _pendingToken->setPrevious(nullptr);

        end->setNext(nullptr);
        _lastToken->setNext(nullptr);
        _lastOutputEnd = _lastToken->begin + _lastToken->size;
        return;
    }

    // everything else
    if (_lastToken == nullptr)
    {
        _startToken = first;
        _lastToken = _pendingToken;
    }
    else
    {
        _lastToken->setNext(first);
        _lastToken = _pendingToken;
    }

    _pendingToken = nullptr;
    _lastOutputEnd = _lastToken->begin + _lastToken->size;
}


void TokenScanner::_applyOffset(TokenPosition* token, int position)
{
    TokenPosition::jumpToFirst(token);

    while (token != nullptr)
    {
        token->offset = position - token->begin - token->size;
        token = token->getNext();
    }
}

bool TokenScanner::_contains(TokenPosition* token, Token::TokenType type)
{
    TokenPosition::jumpToFirst(token);

    while (token != nullptr)
    {
        if (token->token == type)
            return true;

        token = token->getNext();
    }

    return false;
}


/*
 * void TokenScanner::_appendToken(TokenPosition* token)
{
    // make an error if unresolved spaces are between tokens
    if (_lastTokenEnd < token->begin)
        _appendToken(new TokenPosition(Token::ERROR, _lastTokenEnd, token->begin - _lastTokenEnd));

    // move end position of last token
    if (token->begin + token->size > _lastTokenEnd)
        _lastTokenEnd = token->begin + token->size;

    bool accept = _filter & token->token;

    // initial call
    if (_lastToken == nullptr)
    {
        _startToken = token;
        _lastToken = _startToken;
        return;
    }

    // last token is larger then the new token
    if (_lastToken->begin < token->begin && _lastToken->begin + _lastToken->size > token->begin + token->size)
        return;

    auto t = _lastToken;

    // delete Tokens that intersect with the new token (in terms of positioning)
    while (t != nullptr)
    {
        if (t->getPrevious() == token)
            return;

        auto end = t->begin + t->size;
        if (end <= token->begin)
            break;

        auto tmp = t->getPrevious();

        delete t;
        t = tmp;
    }

    if (!accept)
    {
        if (t != nullptr)
            t->setNext(nullptr);

        _lastToken = t;
        delete token;
        return;
    }

    if (t != nullptr)
        t->setNext(token);
    else
        _startToken = token;

    _lastToken = token;
}
 */

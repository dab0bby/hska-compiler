#include "../include/TokenPosition.h"


TokenPosition* TokenPosition::getNext() const
{
    return _next;
}

void TokenPosition::setNext(TokenPosition* next)
{
    _next = next;

    if (next != nullptr)
        next->_previous = this;
}

TokenPosition* TokenPosition::getPrevious() const
{
    return _previous;
}

void TokenPosition::setPrevious(TokenPosition* previous)
{
    _previous = previous;
    
    if (previous != nullptr)
        previous->_next = this;
}

void TokenPosition::deleteAllPrevious(TokenPosition* token)
{
    auto t = token->getPrevious();
    while (t != nullptr)
    {
        auto tmp = t;
        t = t->getPrevious();
        delete tmp;
    }
}

void TokenPosition::deleteAllNext(TokenPosition* token)
{
    auto t = token->getNext();
    while (t != nullptr)
    {
        auto tmp = t;
        t = t->getNext();
        delete tmp;
    }
}

void TokenPosition::offsetAll(TokenPosition* token, int offset)
{
    jumpToFirst(token);    
    for (; token != nullptr; token = token->getNext())
        token->begin += offset;
}

void TokenPosition::jumpToFirst(TokenPosition*& token)
{
    while (token->getPrevious() != nullptr)
        token = token->getPrevious();
}

void TokenPosition::jumpToLast(TokenPosition*& token)
{
    while (token->getNext() != nullptr)
        token = token->getNext();
}

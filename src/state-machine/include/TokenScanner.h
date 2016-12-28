#pragma once
#include "TokenPosition.h"
#include "StateMachine.h"

class TokenScanner
{
public:
    TokenScanner();
    ~TokenScanner();

    void consume(char c);
    void reset();
    int getPosition() const;
    void setPosition(int position);
    void setFilter(int filter);
    int getFilter() const;
    TokenPosition* getTokens() const;

private:
    void _appendToken(TokenPosition* token);
    void _findPosition(TokenPosition* token, TokenPosition*& previous, int& count, TokenPosition*& next) const;
    void _printTokens(TokenPosition* token) const;

    static const int SM_CNT = 22;
    static const int SM_IGN = 0;
    static const int SM_LF = 21;
    static const int SM_IGN_NO_COMMENT = 0;
    
    int _position = 0;
    StateMachine** _sms;
    TokenPosition* _startToken = nullptr;
    TokenPosition* _lastToken = nullptr;
    int _filter =  ~(Token::IGNORE | Token::DETECTING);
    int _lastTokenEnd = 0;
};

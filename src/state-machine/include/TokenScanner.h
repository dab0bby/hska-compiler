#pragma once
#include "TokenPosition.h"
#include "StateMachine.h"
#include <string>

class TokenScanner
{
public:
    TokenScanner();
    ~TokenScanner();

    bool consume(char c);
    void reset();
    int getConsumeCount() const;
    void setFilter(int filter);
    int getFilter() const;
    TokenPosition* getPendingTokens();

private:
    void _appendToken(TokenPosition* token);
    void _mergePendingToken(bool skippedLast);
    static void _applyOffset(TokenPosition* token, int position);
    static bool _contains(TokenPosition* token, Token::TokenType type);

    static const int SM_CNT = 29;
    static const int SM_IGN = 0;
    static const int SM_INT = 5;
    static const int SM_IDFR = 6;
    static const int SM_LF = 21;
    static const int SM_IGN_NO_COMMENT = 0;

    int _position = 0;
    StateMachine** _sms;
    TokenPosition* _startToken = nullptr;
    TokenPosition* _lastToken = nullptr;
    TokenPosition* _pendingToken = nullptr;
    int _filter =  ~(Token::IGNORE | Token::DETECTING);
    int _lastTokenEnd = 0;
    int _lastOutputEnd = 0;
};

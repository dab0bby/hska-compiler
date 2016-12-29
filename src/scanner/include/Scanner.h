#ifndef SCANNER_H_
#define SCANNER_H_


/**
 * @file     Scanner.h
 * @author   Gennadi Eirich
 * @date     30/12/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include "../../buffer/include/Buffer.h"
#include "../../symbol-table/include/SymbolTable.h"
#include "../../state-machine/include/TokenScanner.h"
#include "../../state-machine/include/TokenPosition.h"
#include "../include/Token.h"


class Scanner
{
    public:
        Scanner(Buffer* buffer, SymbolTable* symbolTable, TokenScanner* tokenScanner);
        ~Scanner();

        /**
         *  Returns next Token
         */
        Token* nextToken();

    private:
        Buffer*        _buffer;
        SymbolTable*   _symbolTable;
        TokenScanner*  _tokenScanner;
        TokenPosition* _pendingTokens{ nullptr };

        int  _getTokenBegin(const int& size, const int& offsete) const;

        Token* _createIdentifier(const int& size, const int& offset) const;
        Token* _createInteger(const int& size, const int& offset) const;
        Token* _createError(const int& size, const int& offset) const;
        void   _checkForPendingToken(TokenPosition* tokens);

};


#endif /* SCANNER_H_ */

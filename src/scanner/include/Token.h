#ifndef TOKEN_H
#define TOKEN_H


/**
 * @file     Token.h
 * @author   Bob
 * @date     29/12/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


class Information; // Forward declaration


class Token
{
    public:
        enum TokenType
        {
            DETECTING = 1 << 0,
            ERROR = 1 << 1,
            EOF_TOKEN = 1 << 2,    // End of file token

            PLUS = 1 << 3,
            MINUS = 1 << 4,
            STAR = 1 << 5,
            COLON = 1 << 6,
            INTEGER = 1 << 7,
            IDENTIFIER = 1 << 8,
            SEMICOLON = 1 << 9,
            GREATER = 1 << 10,
            LESS = 1 << 11,
            EQUAL = 1 << 12,
            ASSIGN = 1 << 13,
            EXPRESSION_EQUAL = 1 << 14,
            NOT = 1 << 15,
            AND = 1 << 16,
            BRACKET_OPEN = 1 << 17,
            BRACKET_CLOSE = 1 << 18,
            SQUARE_BRACKET_OPEN = 1 << 19,
            SQUARE_BRACKET_CLOSE = 1 << 20,
            CURLY_BRACKET_OPEN = 1 << 21,
            CURLY_BRACKET_CLOSE = 1 << 22,
            IGNORE = 1 << 23,                     // white spaces and comments
            NEW_LINE = 1 << 24,

            // Keywords
            IF = 1 << 25,
            WHILE = 1 << 26
        };

        Token(TokenType type, const int& line, const int& column);
        Token(TokenType type, const int& line, const int& column, const unsigned int& value);
        Token(TokenType type, const int& line, const int& column, Information* information);
        Token(TokenType type, const int& line, const int& column, const char* errorToken);
        ~Token();

        /**
         * Return TokenType
         * @return
         */
        TokenType getType() const { return _type; }

        /**
         * Return TokenType string of this Token
         */
        const char * getTypeStr() const { return Token::getTokenName(this->_type); }

        /**
         * Returns line number where token was found.
         * @return
         */
        int getLine() const { return _line; }

        /**
         * Returns column number where token was found
         * @return
         */
        int getColumn() const { return _column; }

        /**
         * Returns value
         */
        unsigned int getValue() const { return _value; }

        /**
         * Returns lexem of this token
         */
        const char* getLexem() const;

        /**
         * Returns the error token
         */
        const char* getErrorToken() const;

        /**
         * Return information.
         * Information is nullptr if no Information is present.
         */
        Information* getInformation() const { return _information; };

        /**
         * Return TokenType string to given type
         *
         * @param type
         * @return
         */
        static const char* getTokenName(int type)
        {
            const static char* tokenNames[] =
            {
                "DETECTING",
                "ERROR",
                "EOF_TOKEN",

                "PLUS",
                "MINUS",
                "STAR",
                "COLON",
                "INTEGER",
                "IDENTIFIER",
                "SEMICOLON",
                "GREATER",
                "LESS",
                "EQUAL",
                "ASSIGN",
                "EXPRESSION_EQUAL",
                "NOT",
                "AND",
                "BRACKET_OPEN",
                "BRACKET_CLOSE",
                "SQUARE_BRACKET_OPEN",
                "SQUARE_BRACKET_CLOSE",
                "CURLY_BRACKET_OPEN",
                "CURLY_BRACKET_CLOSE",
                "IGNORE",                     // white spaces and comments
                "NEW_LINE",

                // Keywords
                "IF",
                "WHILE"
            };

            for(int i = 0; i <= 32; i++)
            {
                if (type == 1 << i)
                    return tokenNames[i];
            }

            return "<UNKNOWN>";
        }

    private:
        TokenType _type;
        const int _line;
        const int _column;

        Information*       _information{ nullptr };
        const unsigned int _value;
        const char*        _errorToken;

};


#endif /* TOKEN_H */

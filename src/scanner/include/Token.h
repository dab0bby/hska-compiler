#ifndef TOKEN_H
#define TOKEN_H


/**
 * @file     Token.h
 * @author   Bob
 * @date     20/12/2016
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
            DETECTING,
            ERROR,
            EOF_TOKEN,    // End of file token

            PLUS,
            MINUS,
            STAR,
            COLON,
            INTEGER,
            IDENTIFIER,
            SEMICOLON,
            GREATER,
            LESS,
            EQUAL,
            ASSIGN,
            UNKNOWN_BULLSHIT_OPERATOR,
            NOT,
            AND,
            BRACKET_OPEN,
            BRACKET_CLOSE,
            SQUARE_BRACKET_OPEN,
            SQUARE_BRACKET_CLOSE,
            CURLY_BRACKET_OPEN,
            CURLY_BRACKET_CLOSE,
            IGNORE,                     // white spaces and comments
            NEW_LINE,

            // Keywords
            IF,
            WHILE
        };

        Token(TokenType type, const int& line, const int& column);
        Token(TokenType type, const int& line, const int& column, const unsigned int& value);
        Token(TokenType type, const int& line, const int& column, Information* information);
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
                "UNKNOWN_BULLSHIT_OPERATOR",
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

            return tokenNames[type];
        }

    private:
        TokenType _type;
        const int _line;
        const int _column;

        Information*       _information{ nullptr };
        const unsigned int _value;

};


#endif /* TOKEN_H */

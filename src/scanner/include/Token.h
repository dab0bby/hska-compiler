//
// Created by tim on 04.11.15.
//


#ifndef TOKEN_H
#define TOKEN_H


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
        Token(TokenType type, const int& line, const int& column, const int& value);
        Token(TokenType type, const int& line, const int& column, Information* information);
        ~Token();

        /**
         * Return TokenType
         * @return
         */
        TokenType getType() const { return _type; }

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

        Information* _information{ nullptr };
        int          _value{ 0 };

};


#endif /* TOKEN_H */

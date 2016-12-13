//
// Created by tim on 04.11.15.
//


#ifndef TOKEN_H
#define TOKEN_H


class Token
{
    public:
        enum TokenType
        {
            NONE,
            EOF_TOKEN,    // End of file token

            PLUS,
            MINUS,
            STAR,
            COLON,
            IF,
            WHILE,
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
            ERROR,

            STATE_TBD,      // special state (no valid token found right now)
            STATE_FAILED    // special state (no valid token can be found any further)
        };

        Token(TokenType type, const int& line, const int& column);
        ~Token();

        /**
         * Return TokenType
         * @return
         */
        TokenType getType() const { return _type; }

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
                "NONE",
                "EOF_TOKEN",

                "PLUS",
                "MINUS",
                "STAR",
                "COLON",
                "IF",
                "WHILE",
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
                "ERROR",

                "STATE_TBD",      // special state (no valid token found right now)
                "STATE_FAILED"    // special state (no valid token can be found any further)
            };

            return tokenNames[type];
        }

    private:
        TokenType _type;
        const int _line;
        const int _column;

};


#endif /* TOKEN_H */

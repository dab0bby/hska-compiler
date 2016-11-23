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

    TokenType type;
    int line;
    int column;
    // TODO: Ref to class Information?
};


#endif /* TOKEN_H */

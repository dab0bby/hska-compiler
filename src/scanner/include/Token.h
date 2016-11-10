//
// Created by tim on 04.11.15.
//

#ifndef TOKEN_H
#define TOKEN_H

enum TType {
    //TODO: Add more Token Types
    IDENTIFIER_TYPE,
    OPERATOR_TYPE,
    ERROR_TYPE
};

class Token {
private:
    TType type;
    int line;
    int column;
    // TODO: Ref to class Information?
};


#endif /* TOKEN_H */

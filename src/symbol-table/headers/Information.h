//
// Created by tim on 04.11.15.
//

#ifndef HSKA_COMPILER_INFORMATION_H
#define HSKA_COMPILER_INFORMATION_H

#include "../../scanner/headers/Token.h"

class Information {
private:
    TType type;


public:
    Information(TType type);

    //virtual bool compareLex(char * lexem) = 0;
    //virtual char * getName() = 0;

    TType getType();
};


#endif //HSKA_COMPILER_INFORMATION_H

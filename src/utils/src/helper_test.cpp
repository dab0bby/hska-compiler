//
// Created by timo on 24.11.15.
//

#include "../header/Helper.h"

int main()
{
    int int1, int2;
    char char1, char2;
    double d;
    float f;

    bool success = true;
    success &= Helper::compareTypes(int1, int2);
    success &= Helper::compareTypes(char1, char2);
    success &= !Helper::compareTypes(d, f);
    success &= !Helper::compareTypes(int1, char1);

    return 0;
}
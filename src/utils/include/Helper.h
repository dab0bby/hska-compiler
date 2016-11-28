//
// Created by timo on 24.11.15.
//

#ifndef HSKA_COMPILER_HELPER_H
#define HSKA_COMPILER_HELPER_H

template<typename A, typename B>
struct _isSame { static const bool value = false; };
template<typename A>
struct _isSame<A, A> { static const bool value = true; };

class Helper
{
public:
    // compares two objects and returns true if they have the same type.
    template<typename A, typename B> // template functions can not be split into declaration and definition
    static bool compareTypes(A a, B b)
    {
        return _isSame<A, B>::value;
    }
};

#endif //HSKA_COMPILER_HELPER_H

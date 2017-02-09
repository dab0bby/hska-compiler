//
// Created by timo on 24.11.15.
//

#ifndef HSKA_COMPILER_HELPER_H
#define HSKA_COMPILER_HELPER_H

template<typename A, typename B>
struct _isSame { static const bool value = false; };
template<typename A>
struct _isSame<A, A> { static const bool value = true; };


template<typename A, typename B>
static constexpr bool compareTypes(A a, B b)
{
    return _isSame<A, B>::value;
}

unsigned strlen(const char* str)
{
    unsigned s = 0;
    while (str[s] != '\0')
        s++;

    return s;
}

#endif //HSKA_COMPILER_HELPER_H

//
// Created by timo on 24.11.15.
//

#ifndef HSKA_COMPILER_HELPER_H
#define HSKA_COMPILER_HELPER_H

#include <iostream>
#include <iomanip>

#include "colormod.h"

// if ERROR_IS_EXIT is defined, the app will terminate after the first error
// #define ERROR_IS_EXIT


// region declarations

template <typename Arg1, typename ... Args>
void _errorImpl(Arg1 arg, Args... args);

template <typename Arg>
void _errorImpl(Arg arg);

// endregion

template<typename A, typename B>
struct _isSame { static const bool value = false; };
template<typename A>
struct _isSame<A, A> { static const bool value = true; };


template<typename A, typename B>
static constexpr bool compareTypes(A a, B b)
{
    return _isSame<A, B>::value;
}

inline size_t strlen(const char* str)
{
   unsigned s = 0;
   while (str[s] != '\0')
       s++;

   return s;
}

template <typename ... Args>
void error(int line, int col, Args... msg)
{
    std::cerr << Color::Modifier(Color::FG_RED) << "line " << std::setw(3) << line << ", col " << std::setw(3) << col << ": ";
    _errorImpl(msg...);

#if ERROR_IS_EXIT
    exit(1);
#endif
}

template <typename ... Args>
void error(Args... msg)
{
    std::cerr << Color::Modifier(Color::FG_RED);
    _errorImpl(msg...);

#if ERROR_IS_EXIT
    exit(1);
#endif
}

template <typename Arg1, typename ... Args>
void _errorImpl(Arg1 arg, Args... args)
{
    std::cerr << arg;
    _errorImpl(args...);
}

template <typename Arg>
void _errorImpl(Arg arg)
{
    std::cerr << arg << Color::Modifier(Color::FG_DEFAULT) << std::endl;
}

#endif //HSKA_COMPILER_HELPER_H

/**
 * @file     Buffer_Test.cpp
 * @author   Gennadi Eirich
 * @date     11/11/15
 * @version  1.0
 *
 * @brief    Test source file for the Buffer.
 */


#include <iostream>

#include "../include/Buffer.h"
#include "../../utils/include/colormod.h"


Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier white(Color::FG_DEFAULT);


int main(int argc, char** argv)
{
    std::cout << "--- buffer Test ---\n" << std::endl;

    if (argc != 2)
    {
        if (argc < 2)
            std::cerr << "One Argument is required." << std::endl;
        else
            std::cerr << "Only one argument is allowed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Input file: " << argv[1] << "\n" << std::endl;

    Buffer buffer(argv[1]);

    while (true)
    {
        char c = buffer.nextChar();
        if (c == 0)
        {
            std::cout << "EOF reached" << std::endl;
            break;
        }
//        else if (c == '\n')
//            continue;
        else
            std::cout << buffer.getLineNum() << ":" << buffer.getColumnNum() << "  :  "  << c << std::endl;
    }

    return EXIT_SUCCESS;
}

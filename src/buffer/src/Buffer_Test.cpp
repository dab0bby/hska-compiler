/**
 * @file     Buffer_Test.cpp
 * @author   Gennadi Eirich
 * @date     11/11/15
 * @version  1.0
 *
 * @brief    Test source file for the Buffer.
 *
 */

#include "../headers/Buffer.h"
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    std::cout << "Buffer Test" << std::endl;

    if ( argc != 3 )
    {
        argc < 3 ? fprintf ( stderr, "Less than 2 Argumets." ) : fprintf ( stderr, "Too many arguments." );
        return EXIT_FAILURE;
    }

    std::cout << argv[ 1 ] << std::endl;
    std::cout << argv[ 2 ] << std::endl;

    Buffer*  buffer;
    buffer = new Buffer(  );

    // std::cout << buffer->getChar() << std::cout;

    return EXIT_SUCCESS;
}

/**
 * @file     Scanner_Test.cpp
 * @author   Bob
 * @date     30/12/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include <iostream>
#include <iomanip>
#include <chrono>

#include "../../buffer/include/Buffer.h"
#include "../../symbol-table/include/SymbolTable.h"
#include "../../state-machine/include/TokenScanner.h"
#include "../include/Scanner.h"


#define BENCHMARK 0


int main(int argc, char* argv[])
{
    std::cout << "--- scanner test ---\n" << std::endl;

    if (argc != 2)
    {
        if (argc < 2)
            std::cerr << "One arguments is required." << std::endl;
        else
            std::cerr << "Only one arguments is allowed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Input file: " << argv[1] << "\n" << std::endl;

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    auto buffer = new Buffer(argv[1]);
    auto symbolTable = new SymbolTable();
    auto tokenScanner = new TokenScanner();
    auto scanner = new Scanner(buffer, symbolTable, tokenScanner);

    // Get first token
    auto token = scanner->nextToken();

    while (token->getType() != Token::TokenType::EOF_TOKEN)
    {
#if !BENCHMARK
        std::cout << "Token " << std::setw(26) << std::left << token->getTypeStr()
                  << " Line: " << std::setw(5) << std::left << token->getLine()
                  << " Column: " << std::setw(5) << std::left << token->getColumn();

        if (token->getType() == Token::TokenType::IDENTIFIER)
            std::cout << " Lexem: " << token->getLexem();
        else if (token->getType() == Token::TokenType::INTEGER)
            std::cout << " Value: " << token->getValue();
        else if (token->getType() == Token::TokenType::ERROR)
            std::cout << " Token: " << token->getErrorToken();

        std::cout << std::endl;
#endif
        // Delete token and get new one
        delete token;
        token = scanner->nextToken();
    }

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1000.0 << "ms" << std::endl;

    // Some cleanup
    delete token;
    delete scanner;
    delete tokenScanner;
    delete symbolTable;
    delete buffer;

    return EXIT_SUCCESS;
}

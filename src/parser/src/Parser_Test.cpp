//
// Created by tim on 02.01.17.
//

#include <iostream>
#include <chrono>
#include "../../scanner/include/Scanner.h"
#include "../include/Parser.h"

using namespace std;


int main(int argc, char **argv)
{
    std::cout << "--- parser test ---\n" << std::endl;

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
    // auto start = std::chrono::high_resolution_clock::now();

    auto buffer = new Buffer(argv[1]);
    auto symbolTable = new SymbolTable();
    auto tokenScanner = new TokenScanner();
    auto scanner = new Scanner(buffer, symbolTable, tokenScanner);

    // Do parsing
    auto parser = new Parser(scanner);
    auto tree = parser->parse();
    tree->dumpTree();

    // Cleanup
    delete tree;
    delete parser;
    delete scanner;
    delete tokenScanner;
    delete symbolTable;
    delete buffer;

#ifdef _WIN32
    system("pause");
#endif
}

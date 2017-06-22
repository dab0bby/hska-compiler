/**
 * \author      Bob
 * \date        22/06/2017
 * \version     1.0
 *
 * \brief       ...
 *
 */


#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "buffer/include/Buffer.h"
#include "symbol-table/include/SymbolTable.h"
#include "state-machine/include/TokenScanner.h"
#include "scanner/include/Scanner.h"
#include "parser/include/Parser.h"
#include "parser/include/CodeGenerator.h"


#define BENCHMARK 0
#define SCANNER   0
#define PARSER    1


void _openFile(const char* path, FILE*& file);
void _appendToFile(const Token* token, FILE*& file);
void _closeFile(FILE*& file);


int main(int argc, char **argv)
{
    std::cout << "--- HsKA Compiler ---\n" << std::endl;

    if (argc != 3)
    {
        if (argc < 3)
            std::cerr << "Two arguments are required." << std::endl;
        else
            std::cerr << "Only two arguments are allowed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Input file:  " << argv[1] << std::endl;
    std::cout << "Output file: " << argv[2] << "\n" << std::endl;

#if BENCHMARK
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
#endif // BENCHMARK

    auto buffer = new Buffer(argv[1]);
    auto symbolTable = new SymbolTable();
    auto tokenScanner = new TokenScanner();
    auto scanner = new Scanner(buffer, symbolTable, tokenScanner);

#if SCANNER
    // Open file
    FILE* file = NULL;
    _openFile(argv[2], file);

    // Get first token
    auto token = scanner->nextToken();

    auto hasError = false;

    while (token->getType() != Token::TokenType::EOF_TOKEN)
    {
        if (token->getType() == Token::TokenType::ERROR) // Print to stderr
        {
            hasError = true;

            std::cerr << "Unknown Token  "
                      << "Line: " << std::setw(5) << std::left << token->getLine()
                      << "Column: " << std::setw(5) << std::left << token->getColumn()
                      << "Symbol: " << token->getErrorToken()
                      << std::endl;
        }
        else // Write to file
            _appendToFile(token, file);

        // Delete token and get new one
        delete token;
        token = scanner->nextToken();
    }

    if (!hasError)
        std::cout << "No Errors." << std::endl;

    // Cleanup
    delete token;

    // Close file
    _closeFile(file);

#endif // SCANNER

#if PARSER
    // Parse input
    std::cout << "Parsing . . .           ";
    auto parser = new Parser(scanner);
    auto tree = parser->parse();
    std::cout << "Done\n" << std::endl;

    // Typecheck
    std::cout << "Type checking . . .     ";
    auto valid = tree->typeCheck(tree->getRoot());
    std::cout << "Done\n" << std::endl;

    // Create filestream
    std::ofstream file;
    file.open(argv[2], std::ios::out);

    // Generate code
    std::cout << "Generating code . . .   ";
    auto generator = new CodeGenerator();
    generator->generate(tree->getRoot(), file);
    std::cout << "Done\n" << std::endl;

    // Close file
    file.close();

    // Cleanup
    delete generator;
    delete tree;
    delete parser;
#endif // PARSER

#if BENCHMARK
    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
#endif // BENCHMARK

    // Some cleanup
    delete scanner;
    delete tokenScanner;
    delete symbolTable;
    delete buffer;

#ifdef _WIN32
    system("Pause");
#endif

    return EXIT_SUCCESS;
}


/**
 * Creates a new file
 */
void _openFile(const char* path, FILE*& file)
{
    file = fopen(path, "w");
    if (file == NULL)
    {
        std::cerr << "Error opening file!" << std::endl;
        exit(EXIT_FAILURE);
    }
}


/**
 * Appends token to file
 */
void _appendToFile(const Token* token, FILE*& file)
{
    if (file == NULL)
        return;

    // Write to file
    if (token->getType() == Token::TokenType::IDENTIFIER)
        fprintf(file, "Token %-22s Line: %-5d Column: %-5d Lexem: %s\n", token->getTypeStr(), token->getLine(), token->getColumn(), token->getLexem());
    else if (token->getType() == Token::TokenType::INTEGER)
        fprintf(file, "Token %-22s Line: %-5d Column: %-5d Value: %u\n", token->getTypeStr(), token->getLine(), token->getColumn(), token->getValue());
    else
        fprintf(file, "Token %-22s Line: %-5d Column: %-5d\n", token->getTypeStr(), token->getLine(), token->getColumn());
}


/**
 * Closes the file
 */
void _closeFile(FILE*& file)
{
    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }
}

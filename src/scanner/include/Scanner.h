#ifndef SCANNER_H_
#define SCANNER_H_


/**
 * @file     Scanner.h
 * @author   Gennadi Eirich
 * @date     11/11/15
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include "../../symbol-table/headers/SymbolTable.h"


class Scanner
{
    public:
        Scanner(char*, SymbolTable* symbolTable);
        virtual ~Scanner();

        void nextToken();

    private:

};

#endif /* SCANNER_H_ */

#pragma once


/**
 * @author   Bob
 * @date     14/01/2017
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include <iostream>

#include "Node.h"


class CodeGenerator
{
    public:
        CodeGenerator();
        ~CodeGenerator();

        /**
         * \brief   Generates code for given tree
         *
         * \param   tree    The tree the code should be generated from
         * \param   out     An outsream the code is written to
         */
        void generate(const Node* tree, std::ostream& out);

    private:
        int _labelCount{ 0 };
        const char* _createLabel();

};

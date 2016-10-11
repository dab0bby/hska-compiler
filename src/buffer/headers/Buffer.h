/**
 * @file     Buffer.h
 * @author   Gennadi Eirich
 * @date     11/11/15
 * @version  1.0
 *
 * @brief    ...
 *
 */

#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer
{
    public:
        Buffer();
        virtual ~Buffer();
        char getChar();

    private:
        void openFile(  );
};

#endif /* BUFFER_H_ */

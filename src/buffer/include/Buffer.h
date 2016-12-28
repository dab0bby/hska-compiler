#ifndef BUFFER_H_
#define BUFFER_H_


/**
 * @file     Buffer.h
 * @author   Bob
 * @date     20/12/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


#define HSKA_BUFFER_SIZE 1024


class Buffer
{
    public:
        explicit Buffer(const char* filePath);
        virtual ~Buffer();

        /**
         * Returns the next char.
         *
         * @return char
         */
        char nextChar();

        /**
         * Return the current char.
         *
         * @return
         */
        char currentChar() const;

        /**
         * Returns current Line
         * @return
         */
        unsigned int getLineNum() const;

        /**
         * Returns current Column
         * @return
         */
        unsigned int getColumnNum() const;

        /**
         * Return a string from of given size.
         */
        const char* subStr(const unsigned int size) const;

    private:
        char _currentChar;
        char _previousChar;

        char* _currentBuffer;
        char* _previousBuffer;

        int _fileHandle;

        int          _positionOffset;
        unsigned int _filePositionOffset;
        unsigned int _currentLineNum;
        unsigned int _currentColumnNum;
        bool         _isEof;

        void _alloc(char** buffer);
        void _openFile(const char* filePath);
        void _readNextChunk();
        void _closeFile();

};


#endif /* BUFFER_H_ */

/**
 * @file     Buffer.cpp
 * @author   Bob
 * @date     29/12/2016
 * @version  1.0
 *
 * @brief    ...
 *
 */


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

#include "../include/Buffer.h"


Buffer::Buffer(const char* filePath) :
    _currentChar(0),
    _previousChar(0),
    _fileHandle(-1),
    _positionOffset(-1),
    _filePositionOffset(0),
    _currentLineNum(1),
    _currentColumnNum(0),
    _isEof(false)
{
    // Allocate memory
    _alloc(&_previousBuffer);
    _alloc(&_currentBuffer);

    // Read file
    _openFile(filePath);

    // Read first data chunk
    _readNextChunk();
}


char Buffer::currentChar() const
{
    return this->_previousChar;
}


char Buffer::nextChar()
{
    this->_positionOffset++;
    this->_currentColumnNum++;

    if (this->_positionOffset == this->_filePositionOffset)
        this->_readNextChunk();

    if (this->_previousChar == '\n')
    {
        this->_currentLineNum++;
        this->_currentColumnNum = 1;
    }

    this->_currentChar = this->_currentBuffer[_positionOffset % HSKA_BUFFER_SIZE];
    this->_previousChar = this->_currentChar;

    return this->_currentChar;
}


unsigned int Buffer::getLineNum() const
{
    return _currentLineNum;
}


unsigned int Buffer::getColumnNum() const
{
    return _currentColumnNum;
}


const char* Buffer::subStr(const unsigned int& size, const int& offset) const
{
    char* str = new char[size];

    // Get start position
    int start = (this->_positionOffset % HSKA_BUFFER_SIZE) - size - offset;

    if (start >= 0) // Current buffer
        strncpy(str, this->_currentBuffer + start, static_cast<size_t>(size));
    else // With previous buffer
    {
        // Previous buffer
        int prevBufferStart = HSKA_BUFFER_SIZE + start;
        strncpy(str, this->_previousBuffer + prevBufferStart, static_cast<size_t>(abs(start)));

        // Current buffer
        strncpy(str + abs(start), this->_currentBuffer, static_cast<size_t>(start + size));
    }

    // Add terminator to string
    str[size] = '\0';

    return str;
}


void Buffer::_openFile(const char* filePath)
{
    this->_fileHandle = open(filePath, O_RDONLY);

    if (this->_fileHandle == -1)
        std::cerr << "Error opening file: '" << filePath << "'\n\t" << std::strerror(errno) << std::endl;
}


/**
 * Reads a new data chunck from file
 */
void Buffer::_readNextChunk()
{
    // Don't read if eof is already reached
    if (this->_isEof)
        return;
    if (this->_fileHandle < 0)
        return;

    // Swap buffer pointer
    char* temp = this->_previousBuffer;
    this->_previousBuffer = _currentBuffer;
    this->_currentBuffer = temp;

    // Clear current buffer
    memset(this->_currentBuffer, 0, HSKA_BUFFER_SIZE);

    // Read data from file
    ssize_t size = read(this->_fileHandle, this->_currentBuffer, HSKA_BUFFER_SIZE);

    if (size >= 0)
    {
        this->_filePositionOffset += size;

        // Check if endOfFile is reached
        if (size < HSKA_BUFFER_SIZE)
            this->_isEof = true;
    }
    else
        std::cerr << "Error reading data from file: " << strerror(errno) << std::endl;
}


/**
 * Allocates memory for the buffer
 */
void Buffer::_alloc(char** buffer)
{
    // Allocate memory
    int err = posix_memalign(reinterpret_cast<void**>(buffer), HSKA_BUFFER_SIZE, HSKA_BUFFER_SIZE);

    // Fill buffer with 'nothing'
    memset(*buffer, 0, HSKA_BUFFER_SIZE);

    if (err != 0)
        std::cerr << "Could not allocate buffer memory.\n\tError: " << err << std::endl;
}


/**
 * Closes the file
 */
void Buffer::_closeFile()
{
    int ret = close(this->_fileHandle);
    if (ret < 0)
        std::cerr << "Error closing source file.\n\t" << strerror(errno) << std::endl;
}


Buffer::~Buffer()
{
    // Close file
    _closeFile();

    // Clear buffer
    free(_previousBuffer);
    free(_currentBuffer);
}

//
// TODO: Do not split the code in seperate header and cpp file!
// template classes must have definition and implementation in a single file.
//

// todo: rewrite 50% of this class that the buffer is an array of pointers to the objects and not an array of objects
// reason: It seems that if a new array is initialized, the default constructor of the array-type is called.
//         But if the array-type has no default (parameterless) constructor, the compiler crashes.

//
// Created by timo on 05.11.15.
//

#ifndef HSKA_COMPILER_VECTOR_H
#define HSKA_COMPILER_VECTOR_H
#include <memory>


template <class T>
class vector
{
public:
    vector();
    vector(int initialSize);    
    vector(const vector<T>& copy);    
    ~vector();

    vector<T>& operator=(const vector<T>& other);

    void push_back(const T &t);
    void insert(int index, const T &t);
    void remove(const T &t);
    void remove(int position);
    T& operator [](int position);
    T& operator [](int position) const;

    int size() const;
    int currentCapacity() const;


private:    
    void resize();

    T* buffer;
    int dataSize;
    int bufferSize;

};


template <class T>
vector<T>::vector() : vector(4)
{    
}

template <class T>
vector<T>::vector(int initialSize)
{
    if (initialSize <= 0)
        initialSize = 4;

    dataSize = 0;    
    buffer = new T[initialSize];
    bufferSize = initialSize;
}

template <class T>
vector<T>::vector(const vector<T>& copy) : vector(copy.bufferSize)
{
    for (int i = 0; i < copy.size(); i++)
        buffer[i] = copy[i];    
    
    dataSize = copy.dataSize;    
}

template <class T>
vector<T>& vector<T>::operator=(const vector<T>& other)
{
    delete[] buffer;
    bufferSize = other.bufferSize;
    dataSize = other.dataSize;

    for (int i = 0; i < other.size(); i++)
        buffer[i] = other[i];

    return *this;
}

template <class T>
vector<T>::~vector()
{
    delete[] buffer;
}

template <class T>
void vector<T>::push_back(const T &t)
{
    insert(dataSize, t);
}

template <class T>
void vector<T>::insert(int position, const T &t)
{
    if (position > dataSize || position < 0) 
        return;

    if (dataSize >= bufferSize) 
        resize();

    if (position < dataSize)
        for (int i = dataSize; i > position; i--)    
            buffer[i] = buffer[i - 1];    

    buffer[position] = t;
    dataSize++;
}

template <class T>
void vector<T>::remove(const T &t)
{
    for (int i = 0; i < dataSize; i++)
    {
        if (&(buffer[i]) == &t)
        {
            remove(i);
            break;
        }
    }
}

template <class T>
void vector<T>::remove(int position)
{
    // move all elements after 'position' one level up
    for (int i = position; i < dataSize - 2; i++)
    {
        buffer[i] = buffer[i + 1];
    }

    dataSize--;
}

template <class T>
int vector<T>::size() const
{
    return dataSize;
}

template <class T>
int vector<T>::currentCapacity() const
{
    return bufferSize;
}

template <class T>
void vector<T>::resize()
{
    auto tmp = new T[bufferSize * 2];
    //memcpy(tmp, buffer, bufferSize * sizeof(T));
    for (int i = 0; i < bufferSize; i++)
        tmp[i] = buffer[i];

    delete[] buffer;
    buffer = tmp;
    bufferSize *= 2;
}

template <class T>
T & vector<T>::operator[](int position)
{
    return buffer[position];
}

template <class T>
T & vector<T>::operator[](int position) const
{
    return buffer[position];
}

#endif //HSKA_COMPILER_VECTOR_H
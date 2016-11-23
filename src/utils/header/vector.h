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
    //utils(utils<T> &copy);
    ~vector();

    void add(const T &t);
    void insert(int index, const T &t);
    void remove(const T &t);
    void remove(int position);
    T get(int position) const;
    T& operator [](int position);
    T& operator [](int position) const;

    int size() const;
    int currentCapacity() const;


private:
    void resize();

    T* buffer;
    int index;
    int bufferSize;

};




//
// Created by timo on 05.11.15.
//


template <class T>
vector<T>::vector() : vector(4)
{    
}

template <class T>
vector<T>::vector(int initialSize)
{
    index = 0;
    buffer = new T[initialSize];
    bufferSize = initialSize;
}

template <class T>
vector<T>::vector(const vector<T>& copy) : vector(copy.bufferSize)
{
    for (int i = 0; i < copy.size(); i++)
        buffer[i] = copy[i];    
    
    index = copy.index;    
}

/*
template <class T>
utils::utils(utils<T> &copy)
{
    maxSize = copy.maxSize;
    index = copy.index;
    buffer = new T[copy.maxSize];
    for (int i = 0; i < index; i++) buffer[i] = copy.buffer[i];
}
*/

template <class T>
vector<T>::~vector()
{
    delete[] buffer;
}

template <class T>
void vector<T>::add(const T &t)
{
    insert(index, t);
}

template <class T>
void vector<T>::insert(int position, const T &t)
{
    // position is out of range
    if (position > index) return;

    // array is full -> reallocating memory
    if (index >= bufferSize) resize();

    // move all elements after 'position' one level down
    for (int i = index; i > position; i--)
    {
        buffer[i + 1] = buffer[i];
    }

    // inserting the new element and increment the index (=size())
    buffer[position] = t;
    index++;
}

template <class T>
void vector<T>::remove(const T &t)
{
    for (int i = 0; i < index; i++)
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
    for (int i = position; i < index - 1; i++)
    {
        buffer[i] = buffer[i + 1];
    }

    index--;
}

template <class T>
int vector<T>::size() const
{
    return index;
}

template <class T>
int vector<T>::currentCapacity() const
{
    return bufferSize;
}

template <class T>
void vector<T>::resize()
{
    T *newBuf = new T[bufferSize * 2];

    for (int i = 0; i < bufferSize; i++)
    {
        newBuf[i] = buffer[i];
    }

    delete[] buffer;
    buffer = newBuf;
    bufferSize *= 2;
}

template <class T>
T vector<T>::get(int position) const
{
    return buffer[position];
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
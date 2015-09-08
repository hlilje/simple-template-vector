#include "iterator.h"


// Constructors/destructor

template <typename T>
VectorIterator<T>::VectorIterator() :
    _ptr(nullptr)
{
}

template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator& it) :
    _ptr(it._ptr)
{
}

template <typename T>
VectorIterator<T>::VectorIterator(const T* ptr) :
    _ptr(ptr)
{
}

template <typename T>
VectorIterator<T>::~VectorIterator()
{
}

// Operators

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator=(const VectorIterator& other)
{
    _ptr = other._ptr;
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator=(VectorIterator&& other)
{
    _ptr = other._ptr;
    return *this;
}

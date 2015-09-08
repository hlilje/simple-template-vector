#include "iterator.h"


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

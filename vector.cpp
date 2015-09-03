#ifndef TEMPLATE_VEC

#define TEMPLATE_VEC
#include "vector.h"


// Constructors/destructor

template <typename T>
Vector<T>::Vector()
{
    _num_elements = 0;
    _size = BASE_SIZE;
    _elements = new T[_size];

    clear();
}

template <typename T>
Vector<T>::Vector(std::size_t size)
{
    _num_elements = size;
    if (size < BASE_SIZE)
        size = BASE_SIZE;
    _elements = new T[size];
    _size = size;

    clear();
}

template <typename T>
Vector<T>::Vector(const Vector& other)
{
    T size = other.size();
    _elements = new T[size];
    _size = size;
    _num_elements = size;

    for (unsigned int i = 0; i < _size; ++i)
        _elements[i] = other[i];
}

template <typename T>
Vector<T>::Vector(Vector&& other) :
    _elements(other._elements), _size(other._size),
    _num_elements(other._num_elements)
{
    other._elements = nullptr;
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list)
{
    T size = list.size();
    _elements = new T[size];
    _size = size;
    _num_elements = 0;

    for (auto v : list)
        push_back(v);
}

template <typename T>
Vector<T>::~Vector()
{
    delete [] _elements;
}

// Operators

template <typename T>
T& Vector<T>::operator[](int x)
{
    if (x < 0)
        throw std::out_of_range("negative index");
    else if ((unsigned int) x >= _num_elements)
        throw std::out_of_range("index larger than vector size");
    return _elements[x];
}

template <typename T>
const T& Vector<T>::operator[](int x) const
{
    if (x < 0)
        throw std::out_of_range("negative index");
    else if ((unsigned int) x >= _num_elements)
        throw std::out_of_range("index larger than vector size");
    return _elements[x];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this == &other)
        return *this;
    Vector temp = Vector(other);
    delete [] _elements;
    *this = std::move(temp);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other)
{
    _elements = other._elements;
    _size = other._size;
    _num_elements = other._num_elements;
    other._elements = nullptr;
    return *this;
}

// Private functions

template <typename T>
const void Vector<T>::expand(const int size, const int i)
{
    std::size_t new_size = _size + size;
    T* new_elements = new T[new_size];

    if (i < 0)
        std::copy(_elements, _elements + _size, new_elements);
    else
    {
        std::copy(_elements, _elements + i, new_elements);
        std::copy(_elements + i, _elements + _size - i, new_elements + i + 1);
    }

    delete [] _elements;

    _elements = new_elements;
    _size = new_size;
}

template <typename T>
const void Vector<T>::fill(const T x)
{
    for (unsigned int i = 0; i < _size; ++i)
        _elements[i] = T {x};
}

// Public functions

template <typename T>
const void Vector<T>::push_back(const T x)
{
    if (_num_elements >= _size)
        expand(_size);

    _elements[_num_elements] = x;
    ++_num_elements;
}

template <typename T>
const void Vector<T>::insert(const std::size_t i, const T x)
{
    if (_num_elements >= _size)
        expand(_size, i);
    else
        for(std::size_t j = _num_elements; j > i; --j)
            _elements[j] = _elements[j-1];

    _elements[i] = x;
    ++_num_elements;
}

template <typename T>
const void Vector<T>::clear()
{
    _num_elements = 0;
}

template <typename T>
const void Vector<T>::erase(const std::size_t i)
{
    --_num_elements;

    for(std::size_t j = i; j < _num_elements; ++j)
        _elements[j] = _elements[j+1];
}

template <typename T>
const std::size_t Vector<T>::size() const
{
    return _num_elements;
}

template <typename T>
const std::size_t Vector<T>::capacity() const
{
    return _size;
}

// TODO Vector<T>::begin();

// TODO Vector<T>::end();

// TODO Vector<T>::find(const T&);

#endif

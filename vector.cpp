#include "vector.h"
#include <stdexcept>
#include <iostream>


Vector::Vector()
{
}

Vector::Vector(std::size_t size)
{
    _num_elements = size;
    if (size < BASE_SIZE)
        size = BASE_SIZE;
    _elements = new unsigned int[size];
    _size = size;

    reset();
}

Vector::Vector(const Vector& other)
{
    unsigned int size = other.size();
    _elements = new unsigned int[size];
    _size = size;
    _num_elements = size;

    for (unsigned int i = 0; i < _size; ++i)
        _elements[i] = other[i];
}

Vector::Vector(Vector&& other) :
    _elements(other._elements), _size(other._size),
    _num_elements(other._num_elements)
{
    other._elements = nullptr;
}

Vector::Vector(std::initializer_list<unsigned int> list)
{
    unsigned int size = list.size();
    _elements = new unsigned int[size];
    _size = size;
    _num_elements = 0;

    for (auto v : list)
        add(v);
}

Vector::~Vector()
{
    delete [] _elements;
}

unsigned int& Vector::operator[](int x)
{
    if (x < 0)
        throw std::out_of_range("negative index");
    else if ((unsigned int) x >= _num_elements)
        throw std::out_of_range("index larger than vector size");
    return _elements[x];
}

const unsigned int& Vector::operator[](int x) const
{
    if (x < 0)
        throw std::out_of_range("negative index");
    else if ((unsigned int) x >= _num_elements)
        throw std::out_of_range("index larger than vector size");
    return _elements[x];
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
        return *this;
    Vector temp = Vector(other);
    delete [] _elements;
    *this = std::move(temp);
    return *this;
}

Vector& Vector::operator=(Vector&& other)
{
    _elements = other._elements;
    _size = other._size;
    _num_elements = other._num_elements;
    other._elements = nullptr;
    return *this;
}

const void Vector::expand(const int size)
{
    std::size_t new_size       = _size + size;
    unsigned int* new_elements = new unsigned int[new_size];

    std::copy(_elements, _elements + _size, new_elements);
    delete [] _elements;

    _elements = new_elements;
    _size = new_size;
}

const void push_back(T)
{
    if (_num_elements >= _size)
        expand(_size);

    _elements[_num_elements] = x;
    ++_num_elements; 
}

const void insert(std::size_t, T)
{
}

const void clear()
{
    for (unsigned int i = 0; i < _size; ++i)
        _elements[i] = (unsigned int) {0};
}

const void erase(std::size_t)
{
}

const std::size_t Vector::size() const
{
    return _num_elements;
}

const std::size_t capacity() const
{
}

// TODO begin();

// TODO end();

// TODO find(const T&);

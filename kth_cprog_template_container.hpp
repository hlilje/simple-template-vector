#ifndef TEMPLATE_VEC_H
#define TEMPLATE_VEC_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include "iterator.h"

#define BASE_SIZE 10


template <typename T>
class Vector
{
    private:
        T* _elements;
        std::size_t _size; // Internal container size
        std::size_t _num_elements;

        const void init(std::size_t);
        const void expand(const int, const int i = -1);
        const void fill(const T);
    public:
        Vector();

        explicit Vector(const std::size_t);

        Vector(const std::size_t, const T);

        Vector(const Vector&);

        Vector(Vector&&);

        Vector(const std::initializer_list<T>);

        ~Vector();


        T& operator[](const std::size_t x);

        const T& operator[](const std::size_t x) const;

        Vector& operator=(const Vector&);

        Vector& operator=(Vector&&);


        const void push_back(const T);

        const void insert(const std::size_t, const T);

        const void clear();

        const void erase(const std::size_t);

        const std::size_t size() const;

        const void reset();

        const std::size_t capacity() const;

        VectorIterator<T> begin();

        VectorIterator<T> end();

        VectorIterator<T> find(const T&);
};

#include "vector.cpp"

#endif

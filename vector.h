#ifndef TEMPLATE_VEC_H
#define TEMPLATE_VEC_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

#define BASE_SIZE 10


template <typename T>
class Vector
{
    private:
        T* _elements;
        std::size_t _size; // Actual internal container size
        std::size_t _num_elements;

        const void expand(const int, const int);
    public:
        Vector();

        Vector(const std::size_t);

        Vector(const Vector&);

        Vector(Vector&&);

        Vector(const std::initializer_list<T>);

        ~Vector();


        T& operator[](int x);

        const T& operator[](int x) const;

        Vector& operator=(const Vector&);

        Vector& operator=(Vector&&);


        const void push_back(const T);

        const void insert(const std::size_t, const T);

        const void clear();

        const void erase(const std::size_t);

        const std::size_t size() const;

        const std::size_t capacity() const;

        // TODO begin();

        // TODO end();

        // TODO find(const T&);
};

#include "vector.cpp"

#endif

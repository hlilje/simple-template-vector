#ifndef TEMPLATE_VEC
#define TEMPLATE_VEC

#include "kth_cprog_template_container.hpp"
#define TYPE_ASSERT 0

// Constructors/destructor

template <typename T>
Vector<T>::Vector()
{
#if TYPE_ASSERT
    static_assert(std::is_move_assignable<T>::value, "Type must be Move Assignable");
    static_assert(std::is_move_constructible<T>::value, "Type must be Move Constructible");
#endif

    init(0);
}

template <typename T>
Vector<T>::Vector(const std::size_t size)
{
#if TYPE_ASSERT
    static_assert(std::is_move_assignable<T>::value, "Type must be Move Assignable");
    static_assert(std::is_move_constructible<T>::value, "Type must be Move Constructible");
#endif

    init(size);
}

template <typename T>
Vector<T>::Vector(const std::size_t size, const T init_val)
{
#if TYPE_ASSERT
    static_assert(std::is_move_assignable<T>::value, "Type must be Move Assignable");
    static_assert(std::is_move_constructible<T>::value, "Type must be Move Constructible");
#endif

    init(size);
    fill(init_val);
}

template <typename T>
Vector<T>::Vector(const Vector& other)
{
#if TYPE_ASSERT
    static_assert(std::is_move_assignable<T>::value, "Type must be Move Assignable");
    static_assert(std::is_move_constructible<T>::value, "Type must be Move Constructible");
#endif

    std::size_t size = other.size();
    _elements = new T[size];
    _size = size;
    _num_elements = size;

    for (std::size_t i = 0; i < _num_elements; ++i)
        _elements[i] = other[i];
}

template <typename T>
Vector<T>::Vector(Vector&& other) :
    _elements(other._elements), _size(other._size),
    _num_elements(other._num_elements)
{
#if TYPE_ASSERT
    static_assert(std::is_move_assignable<T>::value, "Type must be Move Assignable");
    static_assert(std::is_move_constructible<T>::value, "Type must be Move Constructible");
#endif

    other._elements = nullptr;
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list)
{
#if TYPE_ASSERT
    static_assert(std::is_move_assignable<T>::value, "Type must be Move Assignable");
    static_assert(std::is_move_constructible<T>::value, "Type must be Move Constructible");
#endif

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
T& Vector<T>::operator[](const std::size_t x)
{
    if (x < 0)
        throw std::out_of_range("Negative index");
    else if (x >= _num_elements)
        throw std::out_of_range("Index larger than vector size");
    return _elements[x];
}

template <typename T>
const T& Vector<T>::operator[](const std::size_t x) const
{
    if (x < 0)
        throw std::out_of_range("Negative index");
    else if (x >= _num_elements)
        throw std::out_of_range("Index larger than vector size");
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
const void Vector<T>::init(std::size_t size)
{
    _num_elements = size;
    if (size < BASE_SIZE)
        size = BASE_SIZE;
    _elements = new T[size];
    _size = size;
}

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
    for (std::size_t i = 0; i < _size; ++i)
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
    if (i == _num_elements)
    {
        push_back(x);
        return;
    }

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

template <typename T>
VectorIterator<T> Vector<T>::begin()
{
    return VectorIterator<T>(_elements);
}

template <typename T>
VectorIterator<T> Vector<T>::end()
{
    return VectorIterator<T>(_elements + _num_elements);
}

template <typename T>
VectorIterator<T> Vector<T>::find(const T& element)
{
    for (std::size_t i = 0; i < _num_elements; ++i)
    {
        if (element == _elements[i])
            return VectorIterator<T>(_elements + i);
    }
    return end();
}

#endif

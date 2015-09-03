#include <algorithm>
#include <cstddef>
#include <initializer_list>

#define BASE_SIZE 10


template <class T>
class Vector
{
    private:
        unsigned int* _elements;
        std::size_t _size; // Actual internal container size
        std::size_t _num_elements;

        const void expand(const int);
    public:
        Vector();

        Vector(std::size_t);

        Vector(const Vector&);

        Vector(Vector&&);

        Vector(std::initializer_list<unsigned int>);

        ~Vector();


        unsigned int& operator[](int x);

        const unsigned int& operator[](int x) const;

        Vector& operator=(const Vector&);

        Vector& operator=(Vector&&);


        const void push_back(T);

        const void insert(std::size_t, T);

        const void clear();

        const void erase(std::size_t);

        const std::size_t size() const;

        const std::size_t capacity() const;

        // TODO begin();

        // TODO end();

        // TODO find(const T&);
};

#include <iterator>


template <typename T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
    private:
        const T* _ptr; // Pointer to element array
    public:
        VectorIterator();

        VectorIterator(const VectorIterator&);

        VectorIterator(const T*);

        ~VectorIterator();


        VectorIterator& operator=(const VectorIterator&);

        VectorIterator& operator=(VectorIterator&&);
};

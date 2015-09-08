#include <iterator>


template <typename T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
    public:
        VectorIterator();

        VectorIterator(const VectorIterator&);

        ~VectorIterator();


        VectorIterator& operator=(const VectorIterator&);

        VectorIterator& operator=(VectorIterator&&);
};

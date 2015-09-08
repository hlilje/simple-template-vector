#include <iterator>


template <typename T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
    private:
        T* _ptr; // Pointer to element array
    public:
        VectorIterator();

        VectorIterator(const VectorIterator&);

        VectorIterator(const T*);

        ~VectorIterator();


        VectorIterator& operator=(const VectorIterator&);


        typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;

        inline VectorIterator& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
        inline VectorIterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}

        inline T& operator*() const {return *_ptr;}
        inline T* operator->() const {return _ptr;}
        inline T& operator[](difference_type rhs) const {return _ptr[rhs];}

        // Prefix
        inline VectorIterator& operator++() {++_ptr; return *this;}
        inline VectorIterator& operator--() {--_ptr; return *this;}
        // Postfix
        inline VectorIterator operator++(int) const {VectorIterator tmp(*this); ++_ptr; return tmp;}
        inline VectorIterator operator--(int) const {VectorIterator tmp(*this); --_ptr; return tmp;}

        // it - it = int
        inline difference_type operator-(const VectorIterator& rhs) const {return VectorIterator(_ptr-rhs.ptr);}
        // it - int = it
        inline VectorIterator operator-(difference_type rhs) const {return VectorIterator(_ptr-rhs);}

        // it + it = int
        inline difference_type operator+(const VectorIterator& rhs) const {return VectorIterator(_ptr+rhs.ptr);}
        // it + int = it
        inline VectorIterator operator+(difference_type rhs) const {return VectorIterator(_ptr+rhs);}

        inline bool operator==(const VectorIterator& rhs) const {return _ptr == rhs._ptr;}
        inline bool operator!=(const VectorIterator& rhs) const {return _ptr != rhs._ptr;}
        inline bool operator>(const VectorIterator& rhs) const {return _ptr > rhs._ptr;}
        inline bool operator<(const VectorIterator& rhs) const {return _ptr < rhs._ptr;}
        inline bool operator>=(const VectorIterator& rhs) const {return _ptr >= rhs._ptr;}
        inline bool operator<=(const VectorIterator& rhs) const {return _ptr <= rhs._ptr;}
};

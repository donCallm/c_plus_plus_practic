#include <new>
#include <cstddef>

constexpr const size_t default_capacity_la = 100;

template <class T>
struct linear_alloc {
    using value_type = T;

    linear_alloc(size_t capacity = default_capacity_la)
        : _buf(new value_type[capacity]),
        _size(0),
        _capacity(capacity)
    {}

    ~linear_alloc() {
        if (_buf) {
            delete[] _buf;
        }
    }

public:
    value_type* allocate(size_t count) {
        if (count > (_capacity - _size)) {
            return new value_type[count];
        }
        _size += count;
        return _buf + (_size - count);
    }

    void deallocate(value_type*& ptr, size_t) {
        if (ptr) {
            if (ptr < _buf || ptr > _buf + _capacity)
                delete[] ptr;
            ptr = nullptr;
        }
    }

    template <typename ...Args>
    void construct(value_type* ptr, Args&&... args) {
        *ptr = value_type(std::forward<Args>(args)...);
    }

    void destroy(value_type* ptr) { 
        ptr->~value_type();
    }

    size_t size() { return _size; }
    size_t capacity() { return _capacity; }

private:
    value_type* _buf;
    size_t _size;
    size_t _capacity;
};

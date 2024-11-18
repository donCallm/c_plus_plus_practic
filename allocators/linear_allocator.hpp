#pragma once

#include <iostream>
#include <new>
#include <cstddef>

template <typename T>
struct linear_alloc {
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;
    typedef T*        pointer;
    typedef const T*  const_pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef T         value_type;
    
    template <class U>
    struct rebind {
        typedef linear_alloc<U> other; };

    linear_alloc()
        : _buf(nullptr),
        _capacity(0),
        _size(0)
    {}

    linear_alloc(size_t capacity)
        : _buf(reinterpret_cast<T*>(new char [sizeof(T) * capacity])),
        _capacity(capacity),
        _size(0)
    {}

    linear_alloc(linear_alloc<T>&& other)
        : _buf(other._buf),
        _capacity(other._capacity),
        _size(other._size)
    {
        other._buf = nullptr;
        other._capacity = 0;
        other._size = 0;
    }
    
    pointer allocate(size_t count) {
        if (count > _capacity || _size + count > _capacity) {
            throw std::runtime_error("there is not enough free memory in the buffer");
        }

        _size += count;
        return _buf + (_size - count);
    }

    void deallocate(pointer, size_t count) {
        if (_size < count)
            throw std::out_of_range("count > _capacity");
        _size -= count;
    }

    template <typename U, typename ...Args>
    void construct(U*, Args&&... args) {
        if (_size == _capacity)
            throw std::out_of_range("capacity is over");
        new(_buf + ++_size) U(args...);
    }

    template <typename U>
    void destruct(U*, size_t index = 0) {
        if (index > _size)
            throw std::out_of_range("index biger then size");
        if (_size == 0)
            throw std::runtime_error("buffer is empty");

        --_size;

        if (index != 0)
            std::swap((_buf + index), (_buf + _size));
    }

    ~linear_alloc() {
        print_size();
        if (_buf == nullptr)
            return;
        delete[] _buf;
    }

    void print_size() {
        std::cout << "SIZE: " << _size << '\n';
    }
    
private:
    pointer _buf;
    size_t _capacity;
    size_t _size;
};

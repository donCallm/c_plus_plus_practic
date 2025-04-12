#pragma once

#include <new>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <iostream>
#include "rnd_access_iterator.hpp"

constexpr const size_t DEFAULT_CAPACITY = 1;
constexpr const size_t INCREASE = 2;
constexpr const size_t END = 2;

template <class T, class All = std::allocator<T>>
struct vector_base {
    using value_type = T;
    using it = rnd_access_iterator<value_type>;
    using const_it = const rnd_access_iterator<value_type>;
    using reverse_it = reverse_rnd_access_iterator<value_type>;
    using const_reverse_it = const reverse_rnd_access_iterator<value_type>;
    // friend struct rnd_access_iterator<value_type>;
    
    vector_base()
        : _buf(nullptr),
        _allocator(All()),
        _size(0),
        _capacity(0)
    {}

    vector_base(std::initializer_list<T> list)
        : _buf(nullptr),
        _allocator(All()),
        _size(list.size()),
        _capacity((list.size() * INCREASE) + END)
    {
        _buf = _allocator.allocate(_capacity);
        auto it = list.begin();
        for(size_t i = 1; i <= _size; ++i, ++it)  // end 0 1 2 3 4 end
            *(_buf + i) = *it;
    }
    
    vector_base(const vector_base<T>& other)
        : _buf(nullptr),
        _allocator(All()),
        _size(other._size),
        _capacity(other._capacity)
    {
        _buf = _allocator.allocate(_capacity);
        for (size_t i = 0; i < _size; ++i)
            *(_buf + i) = other[i];
    }

    vector_base(vector_base<T>&& other) noexcept
        : _buf(other._buf),
        _allocator(All()),
        _size(other._size),
        _capacity(other._capacity)
    {
        other._buf = nullptr;
        other._size = 0;
    }

    vector_base& operator=(const vector_base<T>& other) {
        if (_buf)
            _allocator.deallocate(_buf, _capacity);
        _size = other._size;
        _capacity = other._capacity;
        _buf = _allocator.allocate(_capacity);
        for (size_t i = 0; i < _size; ++i)
            *(_buf + i) = other[i];
    }

    vector_base& operator=(vector_base<T>&& other) {
        if (_buf)
            _allocator.deallocate(_buf, _capacity);
        _size = other._size;
        _capacity = other._capacity;
        _buf = other._buf;
    }

    value_type& operator[](size_t index) {
        return *(_buf + (index + 1));
    }

    ~vector_base() {
        if (_buf)
            _allocator.deallocate(_buf, _capacity);
    }

public:
    it begin() { return it(_buf + 1, 1); } // end(0) 0(1) 1(2) 2(3) 3(4) 4(5) 5(6) 7(8) 9(10) end(11)
    it end() { return it(_buf + _size + 1, _size + 1); }

    it begin() const { return it(_buf + 1, 1); }
    it end() const { return it(_buf + _size, _size); }

    it cbegin() const { return it(_buf + 1, 1); }
    it cend() const { return it(_buf + _size, _size); }

    reverse_it rbegin() { return reverse_it((_buf + _size), _size); }
    reverse_it crbegin() const { return reverse_it((_buf + _size - 1), (_size - 1)); }

    reverse_it rend() { return reverse_it(_buf, 0); }
    reverse_it crend() const { return reverse_it(_buf, 0); }

    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }
    bool empty() const noexcept { return _size == 0; }

    void reserve(size_t size) {
        if (_size == 0) {
            if (_buf != nullptr)
                _allocator.deallocate(_buf, _capacity);
            _capacity = size;
            _buf = _allocator.allocate(size);
            return;
        }
        
        value_type* old = _buf;
        if (_capacity <= _size + 1) {
            _capacity = (_capacity == 0) ? size : _capacity * 2;
        }
        _buf = _allocator.allocate(_capacity);
        copy_old(old, _size);
        _allocator.deallocate(old, _capacity);
    }

    void shrink_to_fit() { _capacity = _size + 2; }

    void push_back(const value_type& value) {
        prepare_buf();
        *(_buf + ++_size) = value;
    }

    void push_back(value_type&& value) {
        prepare_buf();
        *(_buf + ++_size) = value;
    }

    value_type& pop_back() { return _buf + (--_size); }

    it insert(const_it pos, const value_type& value) {
        prepare_buf();
        ++_size;
        forward_shift(pos._index);
        *(_buf + pos._index) = value;
        return it(_buf + pos._index, pos._index);
    }

    it insert(const_it pos, value_type&& value) {
        prepare_buf();
        ++_size;
        forward_shift(pos._index);
        *(_buf + pos._index) = std::move(value);
        return it(_buf + pos._index, pos._index);
    }
    
    template <class ...Args>
    it emplace(const_it pos, Args&&... args) {
        prepare_buf();
        forward_shift(pos._index);
        *(_buf + pos._index) = value_type(std::forward<Args>(args)...);
        return it(_buf + pos._index, pos._index);
    }
    template <class ...Args>
    it emplace_back(Args&&... args) {
        prepare_buf();
        *(_buf + _size++) = value_type(std::forward<Args>(args)...);
        return it((_buf + _size - 1), _size - 1);
    }

    void erase(const_it pos) {
        back_shift(pos._index);
        --_size;
    }

    void clear() { _size = 0; }

private:
    void prepare_buf() {
        if (_capacity == 0 || (_size + 1) >= (_capacity - 1)) {
            if (_capacity == 0)
                _capacity = DEFAULT_CAPACITY;
            reserve(_capacity * INCREASE);
        }
    }

    void copy_old(value_type* old, size_t old_size) {
        for (size_t i = 1; i <= old_size; ++i)
            *(_buf + i) = *(old + i);
    }

    void copy_old(value_type* ptr) {
        copy_old(ptr, _size);
    }

    void forward_shift(size_t index) {               // end(0) 0(1) 1(2) 2(3) 3(4) 4(5) 5(6) 7(8) 8(9) 9(10) new(11) ... end(N)
        for (size_t i = _size + 1; i > index; --i)
            *(_buf + i) = *(_buf + (i - 1));
    }

    void back_shift(size_t index) {
        for (size_t i = index; i < _size; ++i)
            *(_buf + i) = *(_buf + (i + 1));
    }

private:
    value_type* _buf;
    All         _allocator;
    size_t      _size;
    size_t      _capacity;
};

#pragma once

#include <cstddef>
#include "vector_base.hpp"

template <class T>
struct rnd_access_iterator {
    using value_type = T;

    template <class U, class All>
    friend struct vector_base;

    rnd_access_iterator(value_type* value, size_t index)
        : _value(value),
        _index(index)
    {}
    
    value_type& operator->() { return *_value; }
    value_type& operator*() { return *_value; }
    value_type& operator->() const { return *_value; }
    value_type& operator*() const { 
        std::cerr << "INDEX == " << _index << std::endl;
        return *_value;
    }

    virtual value_type* operator++() { 
        ++_index;
        return ++_value;
    }
    virtual value_type* operator--() {
        --_index;
        return --_value;
    }
    virtual value_type* operator++(int) {
        ++_index;
        return _value++;
    }
    virtual value_type* operator--(int) {
        ++_index;
        return _value--;
    }

    virtual rnd_access_iterator<value_type> operator+(int count) {
        return rnd_access_iterator(this->_value + count, this->_index + count);
    }

    virtual rnd_access_iterator<value_type> operator-(int count) {
        return rnd_access_iterator(this->_value - count, this->_index - count);
    }

    bool operator!=(const rnd_access_iterator<value_type>& other) {
        return _index != other._index;
    }

    size_t get_index() { return _index; }

protected:
    value_type* _value;
    size_t      _index;
};

template <class T>
struct reverse_rnd_access_iterator
            : rnd_access_iterator<T>
{
    using value_type = T;

    reverse_rnd_access_iterator(value_type* ptr, size_t index)
        : rnd_access_iterator<value_type>(ptr, index)
    {}


    value_type* operator++() override {
        --(this->_index);
        return --(this->_value);
    }
    value_type* operator--() override {
        ++(this->_index);
        return ++(this->_value);
    }
    value_type* operator++(int) override {
        --(this->_index);
        return this->_value--;
    }
    value_type* operator--(int) override {
        ++(this->_index);
        return this->_value++;
    }
};
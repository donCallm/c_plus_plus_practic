#pragma once

#include "shared_ptr.hpp"
#include <cstddef>
#include <utility>

template <typename T>
struct weak_ptr {
    weak_ptr() {}

    weak_ptr(const shared_ptr<T>& ptr)
        : _cb(ptr._cb),
        _data(ptr._data)
    {
        spinlock sl;
        sl.lock();
        ++(_cb->weak_count);
    }

    bool expire() {
        spinlock sl;
        sl.lock();
        if (_cb == nullptr)
            return true;
        return false;
    }

    shared_ptr<T> lock() {
        spinlock sl;
        sl.lock();
        return shared_ptr<T>(_data, _cb);
    }

    weak_ptr<T>& operator=(const shared_ptr<T>& ptr) {
        _cb = ptr._cb;
        _data = ptr._data;

        spinlock sl;
        sl.lock();
        ++(_cb->weak_count);

        return *this;
    }

    ~weak_ptr() {
        if (_cb->weak_count == 0 && _cb->count == 0) {
            delete _cb;
            delete _data;
        }
        --(_cb->weak_count);
    }

    private:
        typename shared_ptr<T>::control_block* _cb = nullptr;
        T* _data = nullptr;
};

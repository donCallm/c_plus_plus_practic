#pragma once

#include <utility>
#include <cstddef>
#include "spinlock.hpp"

template<class T>
class shared_ptr {
    public:
        shared_ptr() {}

        shared_ptr(T* ptr)
            : _cb(new control_block()),
            _data(ptr)
        {}

        shared_ptr(const T& value)
            : _cb(new control_block()),
            _data(new T(value))
        {
            _cb->count = 1;
        }

        shared_ptr(const shared_ptr<T>& other)
            : _cb(other._cb),
            _data(other._data)
        {
            spinlock sl;
            sl.lock();
            ++(_cb->count);
        }

        template<class U>
        shared_ptr(const shared_ptr<U>& other)
            : _cb(other._cb),
            _data(other._data)
        {
            spinlock sl;
            sl.lock();
            ++(_cb->count);
        }

        shared_ptr(shared_ptr<T>&& other) noexcept
            : _cb(other._cb),
            _data(other._data)
        {
            spinlock sl;
            sl.lock();
            other._data = nullptr;
            other._cb = nullptr;
        }

        ~shared_ptr() {
            spinlock sl;
            sl.lock();

            if (_cb == nullptr) {
                return;
            }
            if (_cb->count == 0 && _cb->weak_count == 0) {
                delete _cb;
                delete _data;
            }
            --(_cb->count);
        }

        T& operator*() const noexcept { return *_data; }
        T* operator->() const noexcept { return _data; }
        T& operator[](size_t index) const { return *(_data + index); }
        shared_ptr<T>& operator=(const shared_ptr<T>& other) {
            _cb = other._cb;
            _data = other._data;
            ++(_cb->count);

            return *this;
        }

    private:
        struct control_block {
            control_block()
                : count(0),
                weak_count(0)
            {}

            size_t count;
            size_t weak_count;
        };

        template <typename U>
        friend struct weak_ptr;

        shared_ptr(T* ptr, control_block* cb)
            : _cb(cb),
            _data(ptr)
        {
            spinlock sl;
            sl.lock();
            ++(_cb->count);
        }

    public:
        T* get() const noexcept {
            spinlock sl;
            sl.lock();
            return _data;
        }
        size_t use_count() const noexcept {
            spinlock sl;
            sl.lock();
            return (_cb == nullptr) ? 0 : _cb->count;
        }
        
    private:
        control_block* _cb = nullptr;
        T*             _data = nullptr;
};

template<class T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    auto ptr = new T(std::forward<Args>(args)...);
    return shared_ptr<T>(ptr);
}

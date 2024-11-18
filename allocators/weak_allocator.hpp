 #pragma once

 #include <new>
 #include <cstddef>

struct weak_alloc {
    template <typename T, typename ...Args>
    T* create(T* ptr, Args&&... args) {
        new(ptr) T(std::forward(args)...);
    }

    template <typename T>
    T* allocate(size_t count) {
        return reinterpret_cast<T*>(new char[sizeof(T) * count]);
    }

    template <typename T>
    void dealocate(T* ptr) {
        delete[] reinterpret_cast<char*>(ptr);
    }

    template <typename T>
    void destroy(T* ptr) {
        ptr->~T();
    }

    template <typename U>
    struct rebind {
        typedef weak_alloc<U> other;
    }
};

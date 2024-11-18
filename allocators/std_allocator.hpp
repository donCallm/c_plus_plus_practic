template <typename T>
struct allocator {
    T* allocate(size_t count) {
        return reinterpret_cast<T*>(new char[count * sizeof(T)]);
    }

    void deallocate(T* ptr, size_t) {
        delete[] ptr;
    }

    template <typename U, typename ...Args>
    void construct(T* ptr, Args&&... args) {
        new (ptr) U(args...);
    }

    template <typename U>
    void destroy(U* ptr) {
        ptr->~T();
    }

    template <typename U>
    struct rebind {
        typedef allocator<U> other;
    };
};

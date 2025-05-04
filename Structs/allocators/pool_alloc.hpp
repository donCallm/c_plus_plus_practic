#include <cstddef>
#include <new>
#include <list>

constexpr const size_t default_capacity_pa = 1000;

template<class T>
struct pool_alloc {
    using value_type = T;

    pool_alloc(size_t capacity = default_capacity_pa)
        : _buf(new value_type[capacity]),
        _capacity(capacity)
    {
        for (size_t i = 0; i < capacity; ++i)
            _pool.emplace_back(block{_buf + sizeof(value_type)});
    }

    ~pool_alloc() { delete[] _buf; }

public:
    value_type* allocate(size_t count) {
        if (count < _pool.size()) {
            int index = find_free_blocs(count);
            if (index == -1)
                return realloc(count);

            prepare_blocks(index, count, operation::reserv);
            return get_block(index)->value;
        } else {
            return realloc(count);
        }
    }

    void deallocate(value_type*& ptr, size_t count) {
        if(ptr) {
            if (ptr < _buf || ptr > _buf + _capacity) {
                delete[] ptr;
            }
            else {
                size_t index = find_block(ptr);
                prepare_blocks(index, count, operation::free);
            }
            ptr = nullptr;
        }
    }

    template<typename ...Args>
    void construct(value_type*& ptr, Args&&... args) {
        if (ptr) {
            if (ptr < _buf && ptr > _buf + _capacity) {
                delete[] ptr;
            } else {
                size_t index = find_block(ptr);
                prepare_blocks(index, 1, operation::free);
            }
            ptr = nullptr;
        }
        ptr = new value_type(std::forward<Args>(args)...);
    }

    void destruct(value_type* ptr) {
        ptr->~value_type();
    }

private:
    enum operation{
        reserv = 0,
        free = 1
    };

    struct block {
        value_type* value;
        bool free = true;
    };

private:
    value_type* realloc(size_t count) const {
        return new value_type[count];
    }

    int find_free_blocs(size_t count) const {
        size_t free_count = -1;
        size_t i = 0;
        for(auto it = _pool.begin(); it != _pool.end() && i < _pool.size(); ++it, ++i) {
            if (it->free) {
                if (++free_count == count)
                    return i - free_count;
            } else {
                free_count = 0;
            }
        }
        return -1;
    }

    void prepare_blocks(size_t index, size_t count, operation op) {
        size_t i = 0;
        switch (op)
        {
            case operation::reserv: {
                for(auto it = _pool.begin(); it != _pool.end() && i < count; ++it, ++i)
                    it->free = false;
                break;
            }
            case operation::free: {
                
                for(auto it = _pool.begin(); it != _pool.end() && i < count; ++it, ++i)
                    it->free = true;
                break;
            }
            default:
                break;
        }
    }

    int find_block(const value_type* ptr) const {
        size_t i = 0;
        for(auto it = _pool.begin(); it != _pool.end(); ++it, ++i) {
            if (ptr >= it->value && ptr < it->value + sizeof(value_type))
                return i;
        }
        return -1;
    }

    block* get_block(size_t index) {
        if (_pool.size() < index)
            return nullptr;
        
        size_t i = 0;
        auto it = _pool.begin();

        while(it != _pool.end() && i < index) {
            ++it;
            ++i;
        }
        
        return &(*it);
    }

private:
    value_type*      _buf;
    std::list<block> _pool;
    size_t           _capacity;
};

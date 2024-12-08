#include <cstddef>
#include <new>
#include <list>

constexpr const size_t default_capacity = 1000;
constexpr const size_t one_block_size = 10;

template<class T>
struct pool_alloc {
    using value_type = T;

    pool_alloc(size_t capacity = default_capacity)
        : _buf(new value_type[size]),
        _size(0)
    {
        for (size_t i = 0; i < size; i += one_block_size)
            _pool.emplace_back(block{_buf + i});
    }

public:
    value_type* allocate(size_t count) {
        if ((count / one_block_size) < _pool.size()) {
            int index = find_free_blocs(count);
            if (index == -1)
                realloc(count);
            prepare_blocks(index, count, operation::reserv);
            return _pool[index].value;
        } else {
            return reallo(count);
        }
    }

    void dealocate(value_type*& ptr, size_t count) {
        if(ptr) {
            if (ptr < _buf && ptr > _buf + (_pool.size() * one_block_size))
                delete[] ptr;
            else {
                size_t index = find_block(ptr);
                prepare_blocks(index, count, operation::free);
            }
            ptr = nullptr;
        }
    }

private:
    value_type* realloc(size_t count) const {
        return new value_type[count];
    }

    int find_free_blocs(size_t count) const {
        size_t free_count = -1;
        for(size_t i = 0; i < _size) {
            if (_pool[i].free) {
                ++free_count;
                if (free_count == count)
                    return free_count;
            } else {
                free_count = 0;
            }
        }
    }

    void prepare_blocks(size_t index, size_t count, opration op) {
        switch (op)
        {
            case operation::reserv: {
                for(size_t i = 0; i < count; ++i)
                    _pool[i].free = false;
                break;
            }
            case operation::free: {
                for(size_t i = 0; i < count; ++i)
                _pool[i].free = true;
                break;
            }
            
            default:
                break;
        }
    }

    int find_block(const value_type* ptr) const {
        for(size_t i = 0; i < _pool.size(); i += one_block_size) {
            if (ptr >= _pool[i].value && ptr < ptr[i + one_block_size])
                return i;
        }
        return -1;
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
    value_type*      _buf;
    std::list<block> _pool;
    size_t           _size;
};

#include <queue>

class Object {};

class ObjectPool {
public:
    ObjectPool(size_t objCount) {
        for(size_t i = 0; i < objCount; ++i) {
            _pool.push(new Object);
        }
    }

    ~ObjectPool() {
        while(!_pool.empty()) {
            delete _pool.front();
            _pool.pop();
        }
    }

public:
    Object* get() {
        if (_pool.empty())
            return nullptr;
        Object* obj = _pool.front();
        _pool.pop();
        return obj;
    }

    void release(Object* obj) {
        if (obj == nullptr)
            return;
        _pool.push(obj);
    }

private:
    std::queue<Object*> _pool;
};

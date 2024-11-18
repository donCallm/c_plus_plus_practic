#pragma once

#include <atomic>

struct spinlock {
    void lock() { while(_flag.test_and_set(std::memory_order_acquire)) {} }

    ~spinlock() { unlock(); }

    private:
        void unlock() { _flag.clear(std::memory_order_release); }

private:
    std::atomic_flag _flag = ATOMIC_FLAG_INIT;
};

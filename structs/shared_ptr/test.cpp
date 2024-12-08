#include "shared_ptr.hpp"
#include "spinlock.hpp"
#include "weak_ptr.hpp"
#include "enable_shared_from_this.hpp"
#include <iostream>
#include <thread>
#include <chrono>

struct base {
    virtual void print() { std::cout << "IS BASE" << std::endl; }
};

struct derived
            : base {
    void print() override { std::cout << "IS DERIVED" << std::endl; }
};

struct dificult_struct {
   dificult_struct() { std::cout << "IS DEFAULT CONSTRUC\n"; } 
   dificult_struct(int) { std::cout << "IS CONSTRUC WITH ONE PARAMS\n"; }
   dificult_struct(int, int) { std::cout << "IS CONSTRUC WITH TWO PARAMS\n"; }
};

struct a;

struct b {
    b(const shared_ptr<a>& _ptr)
        : ptr(_ptr)
    {}
    
    weak_ptr<a> ptr;
};

struct a : enable_shared_from_this<a> {
    a() { ptr = make_shared<b>(shared_from_this()); }

    shared_ptr<b> ptr;
};

void test_shared() {
    std::cout << "TEST SHARED\n";

    {
        std::cout << "test create:\n";
        shared_ptr<int> ptr_i(10);
        
        base* b = new base;
        derived* d = new derived;

        shared_ptr<base*> ptr_b(b);
        shared_ptr<base*> ptr_d(d);

        (*ptr_b)->print();
        (*ptr_d)->print();
    }

    {
        std::cout << "test make_shared:\n";
        auto f_ptr = make_shared<dificult_struct>();
        auto s_ptr = make_shared<dificult_struct>(1);
        auto t_ptr = make_shared<dificult_struct>(1, 1);
    }

    {
        std::cout << "test weak_ptr:\n";
        a temp;
        std::cout << "success\n";
    }
}

void hard_task() {
    spinlock sl;
    sl.lock();
    std::cout << "START HARD TASK\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "OVER HARD TASK\n";
}

void test_spinlock() {
    std::cout << "TEST SPINLOCK\n";
    std::thread t1(hard_task);
    std::thread t2(hard_task);

    t1.join();
    t2.join();
}

#include <iostream>
#include "linear_allocator.hpp"

void linear_alloc_test() {
    std::cout << "-- LINEAR ALLOC --\n\n";

    std::cout << "test allocate:\n";
    linear_alloc<int> empty_alloc;
    linear_alloc<int> normal_alloc(100);
    try {
        empty_alloc.allocate(1);
        std::cout << "empty_alloc::alloc - ERR\n";
    } catch(const std::exception& e) {
        std::cout << "empty_alloc::alloc - SUCCESS\n";
    }
    
    try {
        auto ptr = normal_alloc.allocate(1);
        std::cout << "normal_alloc::alloc - SUCCESS\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cout << "normal_alloc::alloc - ERR\n";
    }

    try {
        for (size_t i = 0; i < 99; ++i)
            auto ptr = normal_alloc.allocate(1);
        
        std::cout << "normal_alloc::alloc_with_for - SUCCESS\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cout << "normal_alloc::alloc - ERR\n";
    }

    try {
        for (size_t i = 0; i < 10; ++i)
            auto ptr = normal_alloc.allocate(1);
        std::cout << "normal_alloc::alloc - ERR\n";
    } catch(const std::exception& e) {
        std::cout << "normal_alloc::alloc_with_full_buf - SUCCESS\n";
    }

    std::cout << "test deallocate:\n";
    try {
        int* temp;
        empty_alloc.deallocate(temp, 1);
        std::cout << "empty_alloc::dealloc - ERR\n";
    } catch(const std::exception& e) {
        std::cout << "empty_alloc::dealloc - SUCCESS\n";
    }

    try {
        int* temp;
        normal_alloc.deallocate(temp, 1);
        std::cout << "normal_alloc::dealloc - SUCCESS\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cout << "normal_alloc::daalloc - ERR\n";
    }

    try {
        int* temp;
        for (size_t i = 0; i < 99; ++i)
            normal_alloc.deallocate(temp, 1);
        std::cout << "normal_alloc::dealloc_with_for - SUCCESS\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cout << "normal_alloc::alloc - ERR\n";
    }

    try {
        int* temp;
        normal_alloc.deallocate(temp, 1);
        std::cout << "normal_alloc::dealloc_after_for - ERR\n";
    } catch(const std::exception& e) {
        std::cout << "normal_alloc::dealloc_after_for - SUCCESS\n";
    }
}

int main() {
    linear_alloc_test();

    return 0;
}
 
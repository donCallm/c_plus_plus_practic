#include <iostream>
#include <cassert>
#include <vector>
#include "linear_allocator.hpp"
#include "pool_alloc.hpp"

void linear_alloc_test() {
    std::cout << "-- LINEAR ALLOC --\n\n";

    {
        std::cout << "test сapacity: ";
        linear_alloc<int> empty_alloc;
        linear_alloc<int> normal_alloc(100);
        assert(empty_alloc.capacity() == normal_alloc.capacity());
        std::cout << "SUCCESS\n";
    }

    {
        std::cout << "test allocate: ";
        linear_alloc<int> alloc;
        int* ptr1 = alloc.allocate(50);
        assert(alloc.size() == 50);

        int* ptr2 = alloc.allocate(100);
        assert(alloc.size() == 50);

        std::cout << "SUCCESS\n";
    }

    {
        std::cout << "test deallocate: ";

        linear_alloc<int> alloc;
        int* ptr = alloc.allocate(150);
        alloc.deallocate(ptr, 150);
        assert(ptr == nullptr);

        std::cout << "SUCCESS\n";
    }
}

int main() {
    // linear_alloc_test();

    std::vector<int, pool_alloc<int>> v;
    for(size_t i = 0; i < 100000; ++i)
        v.push_back(i);

    return 0;
}
 
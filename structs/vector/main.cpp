#include <cassert>
#include <iostream>
#include "vector_base.hpp"

int main() {
    std::cout << "TEST CREATE: ";

    {
        vector_base<int> vec;
    }
    {
        vector_base<int> vec = {1, 2, 3};
        assert(vec.size() == 3);
    }

    std::cout << "create complete\n";
    
    
    std::cout << "TEST PUSH BACK: " << std::flush;

    {
        vector_base<int> vec;
        for (size_t i = 0; i < 100000; ++i)
           vec.push_back(i);
    }
    
    std::cout << "complete\n";

    std::cout << "TEST INSERT: " << std::flush;

    {
        vector_base<int> vec;
        for (size_t i = 0; i < 50000; ++i)
           vec.push_back(i);
        vec.insert(vec.begin() + 25000, 1);
        assert(vec[25000] == 1);
    }

    std::cout << "complete\n";

    std::cout << "TEST ERASE: " << std::flush;

    {
        vector_base<int> vec;
        for (size_t i = 0; i < 50000; ++i)
           vec.push_back(i);
        vec.erase(vec.begin() + 25000);
        assert(vec.size() == 49999);
    }

    std::cout << "complete\n";

    std::cout << "TEST ITEREATORS: {\n" << std::flush;

    {
        vector_base<int> vec;
        for (size_t i = 0; i < 10; ++i)
           vec.push_back(i);

        auto it = vec.begin();
        std::cout << "default: " << std::flush;;
        for(auto it = vec.begin(); it != vec.end(); ++it)
            std::cout << *it << " ";

        std::cout << "\nreverse: " << std::flush;;
        for(auto it = vec.rbegin(); it != vec.rend(); ++it)
            std::cout << *it << " ";
    }

    std::cout << "\n}\n";

    std::cout << "TEST ITEREATORS: {\n" << std::flush;

    {
        
    }

    std::cout << "\n}\n";
    
    return 0;
}

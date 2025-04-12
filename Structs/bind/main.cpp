#include <iostream>
#include "bind.hpp"

void print(int) { std::cout << "ITS WORK!!!\n"; }

int main() {
    {
        bind b(print, 1);
        b();
    }

    {
        bind b(print, std::move(_1));
        b(1);
    }

    return 0;
}

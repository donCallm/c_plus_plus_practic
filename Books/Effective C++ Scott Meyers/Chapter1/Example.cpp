#include <iostream>

namespace TemplateType {
    template <typename T>
    void f(T& param) {}

    template <typename T>
    void f2(const T& param) {}

    template<typename T>
    void f3(T* param) {}

    template<typename T>
    void f4(T&& param) {}

    template<typename T>
    void f5(T param) {}

    void test() {
        int x = 27;
        const int cx = x;
        const int& rx = x;
        const int* px = &x;

        f(x);   // T - int,       param - int&
        f(cx);  // T - const int, param - const int&
        f(rx);  // T - const int`, param - const int&

        f2(x);   // T - int, param - const int&
        f2(cx);  // T - int, param - const int&, const in T no longer needed
        f2(rx);  // T - int, param - const int&

        f3(&x);  // T - int, param - int*
        f3(px);  // T - const int, param - const int*,

        f4(x);   // T - const int&, param - const int&
        f4(cx);  // T - const int&, param - const int&
        f4(rx);  // T - const int&, param - const int&
        f4(27);  // T - int, param - int&&

        f5(x);   // T - int, param - int
        f5(cx);  // T - int, param - int
        f5(rx);  // T - int, param - int

        const char* const ptr = "some";
        f5(ptr); // T - const char*, param - const char*

        const char name [] = "Briggs";
        f5(name); // T - const char*,    param - const char*
        f(name);  // T - const char[7], param - const char[7]

        void someFunc(int, double);
        f5(someFunc); // T - void(*)(int, double), param - void(*)(int, double)
        f(someFunc);  // T - void(&)(int, double), param - void(&)(int, double)
    }
}

namespace AutoType {
    template<typename T>
    void f(T param) {}

    template <typename T>
    void f2(const T param) {}

    template <typename T>
    void f3(const T& param) {}

    template <typename T>
    void f4(std::initializer_list<T> param) {}

    void test() {
        auto x = 27;            // || f(27)
        const auto cx = x;      // || f2(x)
        const auto& rx = &x;    // || f3(x)

        auto&& uref1 = x;       // int&
        auto&& uref2 = cx;      // const int&
        auto&& uref3 = 27;      // int&&

        const char name[] = "some";
        auto arr1 = name;       // const char*
        auto arr2 = name;       // const char[5]

        void someFoo(int, double);
        auto func1 = someFoo;   // void(*)(int, double);
        auto& func2 = someFoo;  // void(&)(int, double);

        auto x1 = 27;           // int
        auto x2(27);            // int
        auto x3{27};            // std::initializer_list<int>

        // f({27}) - Error: cannot infer type
        f4({27});               // std::initializer_list<int>
    }
}

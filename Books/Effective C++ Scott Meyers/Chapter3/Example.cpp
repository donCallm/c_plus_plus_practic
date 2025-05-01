#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include <type_traits>

namespace Braces {
    class Widget {
        public:
            Widget() {}
            Widget(int i, bool b) {} // 1
            Widget(int i, double d) {} // 2
            Widget(std::initializer_list<long double> il) {} // 3

            operator float() const {}

        private:
            int x{0};
            int y = 0;
            // int z(0); Error
    };
    
    void test() {
        std::vector<int> v{1, 3, 5};
        
        double x, y, z;
        // int sum1 { x + y + z }; Error: narrowing transformations
        int sum2(x+y+z); // but its ok
        int sum3 = x + y + z; // its ok too
        // these two options were left to save a lot of old code
        
        // Widget w(); this is treated as a function
        Widget w{}; // calling constructor without params

        Widget w1(10, true); // 1
        Widget w2{10, true}; // 3
        Widget w3(10, 5.0);  // 2
        Widget w4{10, 5.0};  // 3
        // When calling curly braces,
        //it will call the constructor with the initialization sheet

        Widget w5(w4); // calling copy construct
        Widget w6{w4}; // calling operator float -> float convert to long double -> calling 3
        // if operator float not exist - narrowing trans
        Widget w7(std::move(w4)); // calling move construct
        Widget w8(std::move(w4)); // like w6

        std::vector<int> v(10, 20); // 10 elems with value 20
        std::vector<int> v2{10, 20}; // [10, 20]
        // its because vector has constructor with init list
    }
}

namespace Nullptr {
    void f(int) {}
    void f(bool) {}
    void f(void*) {}
    
    class Widget {};

    void f1(std::shared_ptr<Widget>) {}
    void f2(std::unique_ptr<Widget>) {}
    void f3(Widget*) {}

    template <typename FuncType,
        typename MuxType,
        typename PtrType>
    decltype(auto) lockAndCall(FuncType func,
        MuxType& mutex,
        PtrType ptr)
    {
        using MuxGuard = std::lock_quard<MuxType>;
        MuxGuard g(mutex);
        return func(ptr);
    }

    void test() {
        f(0); // f(int)
        // f(NULL); not compile or f(int)
        f(nullptr); // f(void*)
        // nullptr its not ptr, but posible view him like void*

        std::mutex f1m, f2m, f3m;
        using MuxGuard = std::lock_guard<std::mutex>;

        {
            MuxGuard g(f1m);
            f1(0); // implicitly converted to nullptr
        }
        {
            MuxGuard g(f2m);
            f2(NULL); // implicitly converted to nullptr
        }
        {
            MuxGuard g(f3m);
            f3(nullptr);
        }
        // its all work! it bad

        // lockAndCall(f1, f1m, 0); Error: 0 its int
        // lockAndCall(f2, f2m, NULL); Error: NULL its int
        lockAndCall(f3, f3m, nullptr); // Ok

    }
}

namespace Using {
    template <typename T>
    struct MyAlloc {};
    
    template <typename T>
    using MyAllocList1 = std::list<T, MyAlloc<T>>; // simple with using

    template <typename T>
    struct MyAllocList2 {
        typedef std::list<T, MyAlloc<T>> type;
    };

    template <typename T>
    struct Widget {
        private:
            typename MyAllocList2<T>::type list; // only for typedef
    };

    std::remove_reference<int>::type;

    void test() {
        std::remove_reference<int>::type; // typedef C++ 11 version
        std::remove_reference<int>;       // using C++ 14 version
    }
}

namespace EnumWithScope {
    struct First {
        enum e { test };
        // int test; Error - enum test unscoped
        e temp = test; // Ok here
    };

    struct Second {
        enum class e { test };
        int test; // Ok

        // e temp = test; Error
        e temp = e::test; // Ok
    };

    // enum Stats; Error - compiler don know size
    enum class Third; // Ok - he has base type

    enum Stats: std::uint32_t; // its ok, because explicit specify size
    enum class Status: std::uint32_t; // change base type
}

namespace DeleteFunc {
    class Widget {
        Widget() = delete;  
    };

    void foo(int) {}
    void foo(char) = delete;
    void foo(double) = delete;

    template <typename T>
    void foo1(T*) {}

    template <>
    void foo1<char>(char*) = delete;
}

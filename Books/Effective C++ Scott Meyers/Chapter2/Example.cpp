#include <iostream>
#include <memory>
#include <functional>
#include <vector>

namespace Auto {
    class Widget {bool operator<(Widget& other) {return true;}};

    void test() {
        auto derefUPLess = [](const std::unique_ptr<Widget>& p1,
            const std::unique_ptr<Widget>& p2) {
                return *p1 < *p2;
            }; // auto takes up exactly as much space as lambda needs
            
        std::function<bool(const std::unique_ptr<Widget>&, const std::unique_ptr<Widget>&)> 
        derefUPLess2 = [] (const std::unique_ptr<Widget>& p1,
            const std::unique_ptr<Widget>& p2) 
            { return *p1 < *p2; };
        //if the space allocated in the function is not enough, then there will be additional dynamic memory allocations
        // function lambda most slower then auto lambda

        std::vector<bool> vb(10);
        auto temp = vb[0]; // type is std::vector<bool>::reference
        auto temp2 = static_cast<bool>(vb[0]); // type is bool
    }
}

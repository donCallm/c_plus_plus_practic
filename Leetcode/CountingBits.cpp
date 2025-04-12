#include <vector>
#include <bitset>

/*
    Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n),
    ans[i] is the number of 1's in the binary representation of i.

    Example 1:

    Input: n = 2
    Output: [0,1,1]
    Explanation:
    0 --> 0
    1 --> 1
    2 --> 10
    Example 2:

    Input: n = 5
    Output: [0,1,1,2,1,2]
    Explanation:
    0 --> 0
    1 --> 1
    2 --> 10
    3 --> 11
    4 --> 100
    5 --> 101
    

    Constraints:

    0 <= n <= 105
*/

class Solution {
public:
    std::vector<int> countBits(int n) {
        std::vector<int> res;
        res.reserve(n + 1);
        for (size_t i = 0; i <= n; ++i) {
            std::bitset<32> b(i);
            size_t count = 0;
            for(size_t j = 0; j < 32; ++j) {
                if (b[j] == 1) {
                    ++count;
                }
            }
            res.push_back(count);
        }

        return res;
    }
};

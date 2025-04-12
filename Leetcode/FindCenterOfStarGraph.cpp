/*
    There is an undirected star graph consisting of n nodes labeled from 1 to n.
    A star graph is a graph where there is one center node and exactly n - 1 edges
    that connect the center node with every other node.

    You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates
    that there is an edge between the nodes ui and vi. Return the center of the given star graph.

    Example:

    Input: edges = [[1,2],[2,3],[4,2]]
    Output: 2
    Explanation: As shown in the figure above, node 2 is connected to every other node, so 2 is the center.

    Constraints:

    3 <= n <= 105
    edges.length == n - 1
    edges[i].length == 2
    1 <= ui, vi <= n
    ui != vi
    The given edges represent a valid star graph.
*/

#include <vector>
#include <unordered_map>

class Solution {
public:
    int findCenter(std::vector<std::vector<int>>& edges) {
        std::unordered_map<int, int> temp;
        
        for(auto& edge : edges) {
            temp[edge[0]] += 1;
            temp[edge[1]] += 1;
        }

        size_t res = 0;
        size_t max_count;
        for(auto& it : temp) {
            if (it.second == edges.size()) {
                return it.first;
            }
        }

        return -1;
    }
};

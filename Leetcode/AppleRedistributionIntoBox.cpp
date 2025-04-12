#include <vector>
#include <map>

/*
    You are given an array apple of size n and an array capacity of size m.

    There are n packs where the ith pack contains apple[i] apples.
    There are m boxes as well, and the ith box has a capacity of capacity[i] apples.

    Return the minimum number of boxes you need to select to redistribute these n packs of apples into boxes.

    Note that, apples from the same pack can be distributed into different boxes.

    

    Example 1:

    Input: apple = [1,3,2], capacity = [4,3,1,5,2]
    Output: 2
    Explanation: We will use boxes with capacities 4 and 5.
    It is possible to distribute the apples as the total capacity is greater than or equal to the total number of apples.
    Example 2:

    Input: apple = [5,5,5], capacity = [2,4,2,7]
    Output: 4
    Explanation: We will need to use all the boxes.
    

    Constraints:

    1 <= n == apple.length <= 50
    1 <= m == capacity.length <= 50
    1 <= apple[i], capacity[i] <= 50
    The input is generated such that it's possible to redistribute packs of apples into boxes.
*/

class Solution {
public:
    int minimumBoxes(std::vector<int>& apple, std::vector<int>& capacity) {
        int apple_amount = 0;
        for (auto num : apple) // O(n)
            apple_amount += num;
                
        if (capacity.size() == 1) {
            return (apple_amount <= capacity[0]) ? 1 : 0;
        }

        std::map<int, int> backets;
        int start = 0;
        int end = (capacity.size() - 1);

        while(start <= end) { // O(n/2)
            if (start == end) [[unlikely]] {
                backets[capacity[start]] += 1;
                break;
            }
            backets[capacity[start++]] += 1;
            backets[capacity[end--]] += 1;
        }

        int count = 0;
        for (auto it = backets.rbegin(); it != backets.rend(); ++it) { // O(n)
            for(size_t i = 0; i < it->second; ++i) {
                apple_amount -= it->first;
                ++count;
                if (apple_amount <= 0)
                    return count;
            }
        }

        // O(n2)

        return count;
    }
};











def kosaraju(graph):
    stack = []
    visited = set()
    # Первый проход (заполнение стека)
    ----------------
    // O(n)
    def dfs(node):
        for neighbor in graph.get(node, []): // O(n)
    ----------------
    // O(n^2)
    for node in graph: // O(n)
        if node not in visited:
            dfs(node) // O(n)
    ----------------
    # Транспонирование графа
    reversed_graph = {}
    // O(n^2)
    for node in graph: // O(n)
        for neighbor in graph[node]: // O(n)
            reversed_graph.setdefault(neighbor, []).append(node)
    ----------------
    # Второй проход (поиск компонент)
    visited = set()
    components = []
    // O(n) * O(n^2)
    while stack:
        node = stack.pop()
        if node not in visited:
            component = []
            dfs_reversed(node, reversed_graph, visited, component) // O(n^2)
            components.append(component)
    return components

// O(n^2)
def dfs_reversed(node, graph, visited, component):
    visited.add(node)
    component.append(node)
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            dfs_reversed(neighbor, graph, visited, component)

O(n) * O(n^2)

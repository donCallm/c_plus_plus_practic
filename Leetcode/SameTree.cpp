/*
    Given the roots of two binary trees p and q, write a function
    to check if they are the same or not.

    Two binary trees are considered the same if they are structurally
    identical, and the nodes have the same value.
*/

#include <vector>

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void handler(std::vector<int>& store, TreeNode* root) {
    if (!root->left && !root->right) {
        store.push_back(root->val);
        return;
    }
    store.push_back(root->val);
    (root->left) ? handler(store, root->left) : store.push_back(-10001);
    (root->right) ? handler(store, root->right) : store.push_back(-10001);
}

bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if ((!p && q) || (p && !q)) return false;

    std::vector<int> f;
    std::vector<int> s;

    handler(f, p);
    handler(s, q);

    return f == s;
}

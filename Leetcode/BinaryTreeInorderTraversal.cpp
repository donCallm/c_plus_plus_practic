/*
    Given the root of a binary tree, return the inorder traversal of its nodes' values.
*/



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <vector>

class Solution {
public:
    void handler(std::vector<int>& store, TreeNode* root) {
        if (!root->left && !root->right) {
            store.push_back(root->val);
            return;
        }
        if (root->left) handler(store, root->left);
        store.push_back(root->val);
        if (root->right) handler(store, root->right);
    }

    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> res;
        if (!root) {
            return res;
        }
        if (!root->left && !root->right) {
            res.push_back(root->val);
            return res;
        }

        handler(res, root);

        return res;
    }
};

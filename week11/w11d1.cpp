
#include <iostream>
#include <vector>

using std::cout;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int recursiveSum(TreeNode *root, int current)
    {

        if (root == nullptr)
            return 0;

        int updatedCurrent{current * 10 + root->val};

        // This handles the leaves
        if (root->left == nullptr && root->right == nullptr)
            return updatedCurrent;

        return (recursiveSum(root->left, updatedCurrent) + recursiveSum(root->right, updatedCurrent));
    }

    int sumNumbers(TreeNode *root)
    {
        return (recursiveSum(root, 0));
    }
};
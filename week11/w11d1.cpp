
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

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {

        if (root == nullptr)
            return nullptr;

        if (root == p || root == q)
        {
            return root;
        }
        // No Children
        if (root->left == nullptr && root->right == nullptr)
            return nullptr;

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
            return root;

        if (left)
            return left;
        if (right)
            return right;

        return nullptr;
    }
};
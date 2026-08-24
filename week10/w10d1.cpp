#include <iostream>
#include <vector>

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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return false;

        bool hasLeft = (root->left != nullptr) ? true : false;
        bool hasRight = (root->right != nullptr) ? true : false;

        int currentSum = targetSum - root->val;
        // Leaf node logic
        if (!hasLeft && !hasRight)
        {
            if (currentSum == 0)
                return true;
            return false;
        }

        // Explore left
        if (hasLeft)
        {
            if (hasPathSum(root->left, currentSum))
                return true;
        }

        // Explore right
        if (hasRight)
        {
            if (hasPathSum(root->right, currentSum))
                return true;
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
}

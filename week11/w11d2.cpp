#include <iostream>
#include <vector>

using std::cout, std::vector;

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
        void df(TreeNode *root, int currentDepth, int &reportDepth, vector<int> &returnVec)
    {
        if (root == nullptr)
            return;

        if (currentDepth == reportDepth)
        {
            reportDepth += 1;
            returnVec.push_back(root->val);
        }

        if (root->left == nullptr && root->right == nullptr)
            return;

        df(root->right, currentDepth + 1, reportDepth, returnVec);
        df(root->left, currentDepth + 1, reportDepth, returnVec);
    }

    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> returnVec{};
        int reportDepth{0};
        df(root, 0, reportDepth, returnVec);

        return returnVec;
    }
};

int main(int argc, char *argv[])
{
}
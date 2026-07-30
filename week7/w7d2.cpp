#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

using std::vector;

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
private:
    TreeNode *treeBuildRec(const vector<int> &preorder, std::unordered_map<int, int> &inorderMap, int &rootIdx, int left, int right)
    {
        if (left > right)
            return nullptr;
        int rootValue = preorder[rootIdx];
        rootIdx++;

        auto root = new TreeNode(rootValue);

        int inOrderRootIndex = inorderMap[rootValue];
        root->left = treeBuildRec(preorder, inorderMap, rootIdx, left, inOrderRootIndex - 1);
        root->right = treeBuildRec(preorder, inorderMap, rootIdx, inOrderRootIndex + 1, right);

        return root;
    }

public:
    // The preorder list will be the list of nodes we consider the root and the inorder nodes will help us attach the children.
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {

        std::unordered_map<int, int> inorderMap{};
        for (int i{0}; int num : inorder)
        {
            inorderMap[num] = i;
            ++i;
        }

        // construct root
        if (preorder.empty() || inorder.empty())
        {
            return nullptr;
        }

        int rootIdx{0};

        return treeBuildRec(preorder, inorderMap, rootIdx, 0, inorder.size() - 1);
    }
};

int main(int argc, char *argv[])
{
}

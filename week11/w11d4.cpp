#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using std::queue, std::vector, std::pair;

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
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {

        vector<vector<int>> returnVec{};
        if (root == nullptr)
            return returnVec;

        queue<pair<TreeNode *, int>> q{};
        q.push({root, 0});

        while (!q.empty())
        {

            pair<TreeNode *, int> currentNode{q.front()};
            q.pop();
            // Add new level in returnVec
            if (returnVec.size() < currentNode.second + 1)
                returnVec.push_back({});

            returnVec.at(currentNode.second).push_back(currentNode.first->val);

            if (currentNode.first->left != nullptr)
                q.push({currentNode.first->left, currentNode.second + 1});

            if (currentNode.first->right != nullptr)
                q.push({currentNode.first->right, currentNode.second + 1});
        }
        // Reverse odds
        for (int i{0}; i < returnVec.size(); i++)
        {

            if (i % 2 == 0)
            {
                continue
            }
        }

        return returnVec;
    }
};

int main(int argc, char *argv[])
{
}
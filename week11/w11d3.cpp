#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <numeric>

using std::queue, std::vector, std::pair, std::accumulate;

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
    vector<vector<int>> levelOrder(TreeNode *root)
    {

        vector<vector<int>> returnVec{};
        if (root == nullptr)
            return returnVec;

        // Nodes paired with their depth
        queue<pair<TreeNode *, int>> q{};
        q.push({root, 0});

        while (!q.empty())
        {
            // Pop front
            pair<TreeNode *, int> currentPair = q.front();
            q.pop();

            // Sets up the vector container for that level
            if (returnVec.size() < currentPair.second + 1)
                returnVec.push_back({});

            returnVec.at(currentPair.second).push_back(currentPair.first->val);

            // Add children
            if (currentPair.first->left != nullptr)
                q.push({currentPair.first->left, currentPair.second + 1});

            if (currentPair.first->right != nullptr)
                q.push({currentPair.first->right, currentPair.second + 1});
        }

        return returnVec;
    }

    vector<double> averageOfLevels(TreeNode *root)
    {

        vector<vector<int>> nodeOrder{levelOrder(root)};

        vector<double> returnVec{};
        for (const auto &vec : nodeOrder)
        {
            double sum = accumulate(vec.begin(), vec.end(), 0.0);
            returnVec.emplace_back(sum / vec.size());
        }
        return returnVec;
    }
};

int main(int argc, char *argv[])
{
}
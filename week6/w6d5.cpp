#include <iostream>
#include <vector>
#include <string>
#include <queue>

using std::vector, std::string, std::cout, std::queue;

/*
WIP rules for matching - Start with the easiest cases to filter out

1. the total number of 1s should be the same between the source string and the test strings


^ This is the easiest one. We can figure out the number of ones needed from ? if the number is lacking

2. there can never be more 1s accumulated in the test string at a given time compared to the source string.

This is because with the swap, we can only move 1s to the right, and 0s to the left. As such. If there is more 1s
to the left in the test string, it is impossible

We build a prefix table



*/

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
    int maxDepthRecursive(TreeNode *root, int maxDepth)
    {

        if (root->left == nullptr && root->right == nullptr)
        {
            return maxDepth;
        }

        int left{-1};
        int right{-1};

        if (root->left != nullptr)
        {

            left = maxDepthRecursive(root->left, maxDepth + 1);
        }

        if (root->right != nullptr)
        {
            right = maxDepthRecursive(root->right, maxDepth + 1);
        }

        if (left > maxDepth)
        {
            maxDepth = left;
        }

        if (right > maxDepth)
        {
            maxDepth = right;
        }

        return maxDepth;
    }

    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;

        return maxDepthRecursive(root, 1);
    }

    // int maxDepth(TreeNode *root)
    // {
    //     using TreeVec = std::vector<TreeNode *>;

    //     int maxDepth{0};
    //     if (root == nullptr)
    //         return maxDepth;

    //     // Maybe just bfs and track the max number
    //     queue<TreeVec> treeQueue;
    //     treeQueue.push(TreeVec{root});

    //     // Explore neighbors
    //     while (!treeQueue.empty())
    //     {

    //         maxDepth++;
    //         TreeVec newLayer{};
    //         TreeVec oldLayer = treeQueue.front();
    //         treeQueue.pop();
    //         // Unpack TreeVec

    //         for (TreeNode *node : oldLayer)
    //         {
    //             if (node->left != nullptr)
    //                 newLayer.push_back(node->left);
    //             if (node->right != nullptr)
    //                 newLayer.push_back(node->right);
    //         }

    //         if (!newLayer.empty())
    //             treeQueue.push(newLayer);
    //     }

    //     return maxDepth;
    // }

    vector<bool> transformStr(string s, vector<string> &strs)
    {

        // ReturnVector
        vector<bool> returnVec(strs.size(), true);

        // Prefix table
        vector<int> prefix{};
        int currentCount{0};
        for (const char &c : s)
        {
            if (c == '1')
                currentCount++;
            prefix.push_back(currentCount);
        }

        // Loop over strings
        for (int j{0}; j < strs.size(); j++)
        {
            string testString = strs[j];

            int testSOneCount{0};
            int testSQCount{0};
            for (int i{0}; i < testString.size(); i++)
            {
                char c = testString[i];
                if (c == '1')
                    testSOneCount++;
                if (c == '?')
                    testSQCount++;
            }

            // Check for ones count
            if (prefix.back() < testSOneCount)
            {
                returnVec[j] = false;
                continue;
            }

            if (prefix.back() > testSOneCount)
            {

                int neededQ = prefix.back() - testSOneCount;
                if (neededQ > testSQCount)
                {
                    returnVec[j] = false;
                    continue;
                }

                // Now we fill out the rightmost ? with neededQ

                for (int k{(int)testString.size() - 1}; k >= 0 && neededQ > 0; k--)
                {
                    char c = testString[k];
                    if (c == '?')
                    {
                        testString[k] = '1';
                        neededQ--;
                    }
                }
            }

            // Check against prefix

            testSOneCount = 0;
            for (int l{0}; l < testString.size(); l++)
            {
                char c = testString[l];
                if (c == '1')
                    testSOneCount++;

                if (testSOneCount > prefix.at(l))
                {
                    returnVec[j] = false;
                    break;
                }
            }
        }
        return returnVec;
    }
};

int main(int argc, char *argv[])
{
    // string s{"00"};
    // vector<string> test{"11", "1?"};
    // Solution sol;
    // vector<bool> result = sol.transformStr(s, test);

    // for (bool b : result)
    // {
    //     cout << b << ", ";
    // }
}
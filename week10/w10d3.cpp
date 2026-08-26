#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using std::queue, std::vector, std::cout;

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
    /*
    They want an O(n) approach. Technically with a binary tree, with n = V, the complexity of BFS is O(n) because E is always one
    less than V so complexity is bound by O(2N)

    EDIT, they want something that is LESS than O(n)


    */
    int countNodesBFS(TreeNode *root)
    {

        int count{0};
        if (root == nullptr)
            return count;
        queue<TreeNode *> nodeQueue{};

        nodeQueue.push(root);

        while (!nodeQueue.empty())
        {
            TreeNode *currentNode{nodeQueue.front()};
            count++;

            if (currentNode->left != nullptr)
            {
                nodeQueue.push(currentNode->left);
            }

            if (currentNode->right != nullptr)
            {
                nodeQueue.push(currentNode->right);
            }

            nodeQueue.pop();
        }

        return count;
    }

    bool nodeExists(int index, int height, TreeNode *root)
    {

        int mask = 1 << (height - 1);

        while (mask > 0 && root != nullptr)
        {
            if ((index & mask) != 0)
            {
                root = root->right;
            }
            else
            {
                root = root->left;
            }
            mask >>= 1; // Shift mask to check the next bit
        }

        // If we successfully reached a valid node, return true
        if (root != nullptr)
        {
            return true;
        }
        return false;
    }

    // Lets take a binary search approach
    int countNodes(TreeNode *root)
    {

        if (root == nullptr)
            return 0;

        // get leftmost node and depth
        int maxDepth{1};
        TreeNode *leftMost = root;
        while (leftMost->left != nullptr)
        {
            leftMost = leftMost->left;
            maxDepth++;
        }

        int maxLeaves{(int)std::pow(2, maxDepth - 1)};

        int left{0};
        int right{maxLeaves - 1};

        while (left < right)
        {
            int mid{left + ((right - left) / 2)};
            bool exists{nodeExists(mid, maxDepth - 1, root)};

            if (exists)
            {
                if (!nodeExists(mid + 1, maxDepth - 1, root))
                {
                    left = mid;
                    break;
                }

                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return (int)std::pow(2, maxDepth - 1) - 1 + left + 1;
    }
};

int main(int argc, char *argv[])
{
}
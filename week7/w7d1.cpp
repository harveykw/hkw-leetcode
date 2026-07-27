#include <iostream>
#include <vector>
#include <string>
#include <queue>

using std::vector, std::string, std::cout, std::queue;

/*
We just walk through the tree

req values are the same
structure is the same

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
    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        // If one or both of the children are null. I might not need this actually. This is because the following functions handle null cases.
        // if ((root->left == nullptr) || (root->right == nullptr))
        // {
        //     return (root->left == root->right);
        // }

        // Lets invert the right one to get its mirror
        inversion(root->right);

        return isSameTree(root->left, root->right);
    }

    void inversion(TreeNode *root)
    {
        if (root == nullptr)
            return;

        std::swap(root->left, root->right);

        invertTree(root->left);
        invertTree(root->right);
    }

    TreeNode *invertTree(TreeNode *root)
    {
        inversion(root);
        return root;
    }

    bool isSameTree(TreeNode *p, TreeNode *q)
    {

        if (p == nullptr || q == nullptr)
            return p == q;

        queue<TreeNode *> treeQueueP{}, treeQueueQ{};

        treeQueueP.push(p);
        treeQueueQ.push(q);

        while (!treeQueueP.empty())
        {

            // Pattern match
            if (treeQueueP.size() != treeQueueQ.size())
                return false;
            TreeNode *treeP = treeQueueP.front();
            TreeNode *treeQ = treeQueueQ.front();

            treeQueueP.pop();
            treeQueueQ.pop();

            // Bad value
            if (treeP->val != treeQ->val)
                return false;

            // Only runs if one is a nullpointer
            if ((treeP->left == nullptr) != (treeQ->left == nullptr))
                return false;
            if ((treeP->right == nullptr) != (treeQ->right == nullptr))
                return false;

            // If both are not nullpointers
            if (treeP->left != nullptr && treeQ->left != nullptr)
            {
                treeQueueP.push(treeP->left);
                treeQueueQ.push(treeQ->left);
            }

            if (treeP->right != nullptr && treeQ->right != nullptr)
            {
                treeQueueP.push(treeP->right);
                treeQueueQ.push(treeQ->right);
            }
        }
        return true;
    }
};

void printTreeBFS(TreeNode *root)
{
    if (root == nullptr)
        return;

    queue<TreeNode *> treeQueue{};
    treeQueue.push(root);

    while (!treeQueue.empty())
    {
        auto node = treeQueue.front();
        if (node->left != nullptr)
            treeQueue.push(node->left);
        if (node->right != nullptr)
            treeQueue.push(node->right);

        treeQueue.pop();

        cout << node->val << ", ";
    }
}

int main(int argc, char *argv[])
{
    TreeNode s3{1};
    TreeNode s1{0, &s3, nullptr};

    //     TreeNode t3{1};
    //     TreeNode t1{0, &t3, nullptr};

    TreeNode p2{2};
    TreeNode p3{3};
    TreeNode p1{1, &p2, &p3};

    TreeNode q2{2};
    TreeNode q3{3};
    TreeNode q1{1, &q3, &q2};

    TreeNode r1{10, &p1, &q1};

    Solution sol{};
    // printTreeBFS(sol.invertTree(&p1));
    cout << sol.isSymmetric(&r1);
}
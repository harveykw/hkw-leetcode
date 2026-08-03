#include <iostream>
#include <vector>
#include <queue>

using std::queue, std::vector;

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    Node *connect(Node *root)
    {

        if (root == nullptr)
            return nullptr;

        queue<vector<Node *>> layerQueue{};
        layerQueue.push({root});

        while (!layerQueue.empty())
        {

            vector<Node *> &currentLayer = layerQueue.front();
            vector<Node *> newLayer{};
            for (int i{0}; i < currentLayer.size(); i++)
            {

                // Set next
                currentLayer.at(i)->next = (i + 1 < currentLayer.size()) ? currentLayer.at(i + 1) : NULL;

                if (currentLayer.at(i)->left != nullptr)
                    newLayer.push_back(currentLayer.at(i)->left);
                if (currentLayer.at(i)->right != nullptr)
                    newLayer.push_back(currentLayer.at(i)->right);
            }

            if (newLayer.empty())
                return root;

            layerQueue.push(newLayer);
            layerQueue.pop(); // Old layer
        }
        return root;
    }
};

int main(int argc, char *argv[])
{
}
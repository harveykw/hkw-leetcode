#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    Node *recursiveClone(Node *node, vector<Node *> &visited)
    {
        if (node == nullptr)
            return nullptr;

        Node *clonedNode = new Node(node->val);
        visited.at(clonedNode->val - 1) = clonedNode;

        for (Node *neighbor : node->neighbors)
        {
            int neighborIndex{neighbor->val - 1}; // One indexed
            if (visited.at(neighborIndex) != nullptr)
            { // If neighbor's clone already exists
                clonedNode->neighbors.push_back(visited.at(neighborIndex));
                continue;
            }

            clonedNode->neighbors.push_back(recursiveClone(neighbor, visited));
        }

        return clonedNode;
    }

    Node *cloneGraph(Node *node)
    {
        // Create data structure to hold visited nodes
        // We dont use bool vectors in c++ because it is space optimized and they pack bits. Direct pointers and refs dont work with bool vectors.
        vector<Node *> visited(100, nullptr);

        return recursiveClone(node, visited);
    }
};

int main(int argc, char *argv[])
{
}
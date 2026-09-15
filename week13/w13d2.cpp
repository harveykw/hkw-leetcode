#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector, std::unordered_map;

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {

        if (head == nullptr)
            return nullptr;

        Node *newHead = nullptr;
        unordered_map<Node *, Node *> nodeMap{};

        // Walk through original list

        Node dummy(0);
        Node *tail = &dummy;

        while (head != nullptr)
        {

            // create clone and copy value

            if (nodeMap.find(head) == nodeMap.end())
            {
                tail->next = new Node(head->val);
                // Add mapping
                nodeMap[head] = tail->next;
            }
            else
            {
                tail->next = nodeMap[head];
            }

            // create random if does not exist

            if (head->random == nullptr)
            {
                tail->next->random = nullptr;
            }
            else
            {
                if (nodeMap.find(head->random) == nodeMap.end())
                {
                    tail->next->random = new Node(head->random->val);
                    nodeMap[head->random] = tail->next->random;
                }
                else
                {
                    tail->next->random = nodeMap[head->random];
                }
            }

            head = head->next;
            tail = tail->next;
        }

        return dummy.next;
    }
};

int main(int argc, char *argv[])
{
}
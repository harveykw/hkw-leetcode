#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        // No need to handle null case

        // Linked lists can be different lengths

        vector<int> accumulatedDigits{};

        bool carry{false};

        while (l1 != nullptr || l2 != nullptr)
        {

            accumulatedDigits.push_back(0);
            if (l1 != nullptr)
                accumulatedDigits.back() += l1->val;
            if (l2 != nullptr)
                accumulatedDigits.back() += l2->val;

            // carry flip
            if (carry)
            {
                accumulatedDigits.back() += 1;
                carry = false;
            }

            // carrydigit
            if (accumulatedDigits.back() >= 10)
            {
                accumulatedDigits.back() = accumulatedDigits.back() % 10;
                carry = true;
            }

            if (l1 != nullptr)
                l1 = l1->next;

            if (l2 != nullptr)
                l2 = l2->next;
        }

        if (carry)
            accumulatedDigits.push_back(1);

        std::reverse(accumulatedDigits.begin(), accumulatedDigits.end());

        // build linked list
        ListNode *head = nullptr;

        for (const int &digit : accumulatedDigits)
        {
            head = new ListNode(digit, head);
        }

        return head;
    }
};

int main(int argc, char *argv[])
{
}
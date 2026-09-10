#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_set>

using std::vector, std::string;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    string reverseWords(string s)
    {

        string returnString{""};

        std::istringstream iss(s);

        string word{};

        vector<string> words{};

        while (iss >> word)
        {
            words.push_back(word);
        }

        std::reverse(words.begin(), words.end());

        for (int i{0}; i < words.size(); ++i)
        {

            if (i != 0)
            {
                returnString += " ";
            }

            returnString += words.at(i);
        }

        return returnString;
    }

    // There is a two pointer technique for determining cycles in linked lists

    bool hasCycle(ListNode *head)
    {

        if (head == nullptr)
        {
            return false;
        }

        std::unordered_set<ListNode *> visitedSet{};

        while (head->next != nullptr)
        {
            visitedSet.insert(head);

            if (visitedSet.find(head->next) != visitedSet.end())
            {
                return true;
            }
            head = head->next;
        }

        return false;
    }
};

int main(int argc, char *argv[])
{

    string test1{""};
    Solution sol{};
    std::cout << sol.reverseWords(test1);
}
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

// Keep in mind for cases where

// String is all open, with no closes

// String starts with a close

bool isValid(string s)
{
    // Check for odds
    if (s.length() % 2 != 0)
    {
        return false;
    }

    stack<char> letterStack{};

    unordered_map<char, char> mapping{
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}};

    for (const char c : s)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            letterStack.push(c);
        }
        else
        {
            if (letterStack.empty() || mapping[letterStack.top()] != c)
            {
                return false;
            }
            else
            {
                letterStack.pop();
            }
        }
    }

    if (letterStack.size() != 0)
        return false;
    return true;
}

int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> letterBank{};
    string::iterator it1 = s.begin(); // Right bound
    string::iterator it2 = s.begin(); // Left bound

    int maxLength{0};

    for (int i{0}; i < s.length(); i++)
    {
        // Rightbound iterator logic
        letterBank[*it1]++;

        // Leftbound iterator logic
        if (letterBank[*it1] > 1)
        {
            // Initiate leftbound advance
            while (letterBank[*it1] > 1)
            {
                letterBank[*it2]--;
                it2++;
            }
        }

        // Rightbound advance
        it1++;

        // Calculate current length + update
        int currentLength = distance(it2, it1);
        if (currentLength > maxLength)
            maxLength = currentLength;
    }
    return maxLength;
}

int main(int argc, char *argv[])
{
    string test{"){"};
    cout << isValid(test);
}
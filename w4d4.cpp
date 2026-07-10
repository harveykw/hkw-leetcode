#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

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
    string test{"abcabcbb"};
    cout << lengthOfLongestSubstring(test);
}
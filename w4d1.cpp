#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool isAnagram(string s, string t)
{
    if (s.length() != t.length())
        return false;

    unordered_map<char, int> letterBank{};

    // Load s into letter bank
    for (const char c : s)
    {
        letterBank[c]++;
    }

    // Check letterBank for all elements of t
    for (const char c : t)
    {
        if (letterBank.find(c) != letterBank.end())
        {
            if (letterBank[c] <= 0)
            {
                return false;
            }
            else
            {
                letterBank[c]--;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    string testS{"anagraxm"};
    string testT{"nagarzam"};

    cout << isAnagram(testS, testT);
}
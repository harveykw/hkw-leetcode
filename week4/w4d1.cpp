#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// This function is destructive to the input argument
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    // The key of the map will be the sorted version of the word being tested
    unordered_map<string, vector<string>> wordMap{};
    vector<vector<string>> returnList{};

    for (string s : strs)
    {
        string original = s;
        sort(s.begin(), s.end());

        wordMap[s].push_back(original);
    }

    for (const auto &[key, value] : wordMap)
    {
        returnList.push_back(value);
    }
    return returnList;
}

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
    // string testS{"anagraxm"};
    // string testT{"nagarzam"};

    // cout << isAnagram(testS, testT);

    vector<string> test{"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result = groupAnagrams(test);

    for (const vector<string> s : result)
    {
        for (const string str : s)
        {
            cout << str << ", ";
        }
        cout << endl;
    }
}
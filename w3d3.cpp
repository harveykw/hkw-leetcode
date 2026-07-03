#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

bool isIsomorphic(string s, string t)
{

    unordered_map<char, char> letterMap1{};
    unordered_map<char, char> letterMap2{};

    for (int i{0}; i < s.size(); i++)
    {
        // set mapping
        if (letterMap1.find(s[i]) != letterMap1.end())
        {
            if (letterMap1[s[i]] != t[i])
                return false;
        }
        else
        {
            letterMap1[s[i]] = t[i];
        }

        if (letterMap2.find(t[i]) != letterMap1.end())
        {
            if (letterMap2[t[i]] != s[i])
                return false;
        }
        else
        {
            letterMap2[t[i]] = s[i];
        }
    }

    return true;
}

// Remember to hand out of bounds
bool wordPattern(string pattern, string s)
{
    unordered_map<char, string> letterMap1{};
    unordered_map<string, char> letterMap2{};

    istringstream iss(s);
    string currentWord;

    // Extracting words from the string
    int index{0};
    while (iss >> currentWord)
    {
        char c = pattern[index];

        // Char to String Mapping
        // If we do find the char in the bank
        if (letterMap1.find(c) != letterMap1.end())
        {
            // Validate the corresponding word with the value from the bank
            if (currentWord != letterMap1[c])
                return false;
        }
        else
        {
            // Brand new char, we add mapping
            letterMap1[c] = currentWord;
        }

        // String to Char mapping
        if (letterMap2.find(currentWord) != letterMap2.end())
        {
            if (c != letterMap2[currentWord])
                return false;
        }
        else
        {
            letterMap2[currentWord] = c;
        }
        ++index;
    }
    if (index != pattern.size())
        return false;

    return true;
}

int main(int argc, char *argv[])
{
    string test1{"abba"};
    string test2{"dog cat cat dog"};

    cout << wordPattern(test1, test2);
}
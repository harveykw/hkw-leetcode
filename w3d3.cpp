#include <iostream>
#include <string>
#include <unordered_map>

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
            {
                return false;
            }
        }
        else
        {
            letterMap1[s[i]] = t[i];
        }

        if (letterMap2.find(t[i]) != letterMap1.end())
        {
            if (letterMap2[t[i]] != s[i])
            {
                return false;
            }
        }
        else
        {
            letterMap2[t[i]] = s[i];
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    string test1{"paper"};
    string test2{"title"};

    cout << isIsomorphic(test1, test2);
}
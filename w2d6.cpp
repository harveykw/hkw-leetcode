#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int hIndex(vector<int> &citations)
{
    sort(citations.begin(), citations.end());

    vector<int>::iterator it = citations.end() - 1;

    int hIndex{0};

    while (hIndex < *it)
    {
        hIndex++;
        if (it == citations.begin())
            return hIndex;
        it--;
    }

    return hIndex;
}

int strStr(string haystack, string needle)
{
    int possibleIndex{-1};
    if (haystack.empty() || needle.empty() || needle.length() > haystack.length())
        return possibleIndex;

    int offset{0};
    for (int i{0}; i < haystack.length(); i++)
    {
        char curChar{haystack[i]};

        if (curChar == needle[offset])
        {
            if (possibleIndex == -1)
                possibleIndex = i;
            offset++;
        }
        else
        {
            if (possibleIndex != -1)
                i = possibleIndex;
            offset = 0;
            possibleIndex = -1;
        }

        if (offset == needle.size())
        {
            return possibleIndex;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{

    // vector<int> test{3, 0, 6, 1, 5};
    string test1{"mississippi"};
    string test2{"issip"};
    cout << strStr(test1, test2);
}
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool isSubsequence(string s, string t)
{
    int subseqSize{(int)s.length()};
    int subseqIndex{0};

    if (s.empty() && t.empty())
        return true;

    for (const char c : t)
    {
        if (subseqIndex < subseqSize && s[subseqIndex] == c)
        {
            subseqIndex++;
        }

        if (subseqIndex == subseqSize)
        {
            return true;
        }
    }

    return false;
}

int findVolume(int distance, int shortest)
{
    return distance * shortest;
}

int maxArea(vector<int> &height)
{

    vector<int>::iterator it1{height.begin()};
    vector<int>::iterator it2{height.end() - 1};

    int currentMaxVolume{0};
    while (it1 < it2)
    {
        // calculate current volume
        int shortest = (int)min(*it1, *it2);
        int distance = std::distance(it1, it2);
        int currentVolume = findVolume(distance, shortest);

        if (currentVolume > currentMaxVolume)
        {
            currentMaxVolume = currentVolume;
        }

        if (*it1 < *it2)
        {
            it1++;
        }
        else
        {
            it2--;
        }
    }

    return currentMaxVolume;
}

int main(int argc, char *argv[])
{
    vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};

    cout << maxArea(height);
}
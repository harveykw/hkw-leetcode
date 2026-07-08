#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool isHappy(int n)
{
    vector<int> digitArray{};
    unordered_map<int, int> seen{};

    while (n != 1)
    {
        digitArray.clear();
        int temp = n;
        while (temp > 0)
        {
            digitArray.push_back(temp % 10);
            temp /= 10;
        }

        int newSum{0};
        for (const int i : digitArray)
        {
            newSum += (i * i);
        }

        if (seen.find(newSum) == seen.end())
        {
            seen[newSum] = -1;
        }
        else
        {
            return false;
        }

        n = newSum;
    }

    return true;
}

int longestConsecutive(vector<int> &nums)
{

    if (nums.size() == 0)
        return 0;

    sort(nums.begin(), nums.end());

    int maxLength{1};
    int currentLength{1};
    vector<int>::iterator it = nums.begin();
    while (it < nums.end())
    {

        if (it + 1 != nums.end())
        {
            if (((*it) + 1 == *(it + 1)))
            {
                ++currentLength;
                if (currentLength > maxLength)
                {
                    maxLength = currentLength;
                }
            }
            else
            {
                if ((*it) != *(it + 1))
                {
                    currentLength = 1;
                }
            }
        }

        it++;
    }
    return maxLength;
}

int main(int argc, char *argv[])
{
    vector<int> test{-10, -11, 4};
    int testNum{210};

    cout << isHappy(testNum);
}
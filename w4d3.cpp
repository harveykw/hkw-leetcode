#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

int minSubArrayLen(int target, vector<int> &nums)
{

    int minimalLength{0};
    bool solExists{false};

    int currentWindowSum{0};
    vector<int>::iterator it1 = nums.begin();
    vector<int>::iterator it2 = nums.begin();

    for (int i{0}; i < nums.size(); i++)
    {
        currentWindowSum += *it1;
        it1++;

        if (currentWindowSum >= target)
        {
            // Reduce left edge
            bool reduce{true};
            while (reduce)
            {
                if (currentWindowSum - *it2 >= target)
                {
                    currentWindowSum -= *it2;
                    it2++;
                }
                else
                {
                    reduce = false;
                }
            }

            // Updates minimum length
            int windowSize = distance(it2, it1);
            if (solExists)
            {
                if (windowSize < minimalLength)
                {
                    minimalLength = windowSize;
                }
            }
            else
            {
                minimalLength = windowSize;
                solExists = true;
            }
        }
    }
    return minimalLength;
}

bool containsNearbyDuplicate(vector<int> &nums, int k)
{
    unordered_map<int, int> numBank{};

    for (int i{0}; i < nums.size(); i++)
    {
        if (numBank.find(nums[i]) == numBank.end())
        {
            numBank[nums[i]] = i;
        }
        else
        {
            if (abs(numBank[nums[i]] - i) <= k)
            {
                return true;
            }
            else
            {
                numBank[nums[i]] = i;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    vector<int> test{1, 1, 1, 1, 1, 1, 1, 1};
    cout << minSubArrayLen(11, test);
}
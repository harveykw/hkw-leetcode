#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

int removeElement(vector<int> &nums, int val)
{

    // We will map key = index, value = face value
    unordered_map<int, int> map;
    int indexToWrite{0};

    // Set up the read loop
    for (int &i : nums)
    {
        if (i != val)
        {
            map[indexToWrite] = i;
            indexToWrite++;
        }
    }

    for (const auto &[key, value] : map)
    {
        nums[key] = value;
    }

    return indexToWrite;
}

/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

We exploit sorded lists. We also do deduplication of values to prevent repeats

*/

vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); ++i)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue; // skip duplicate first value
        }

        int left = i + 1;
        int right = nums.size() - 1;

        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum < 0)
            {
                left++;
            }
            else if (sum > 0)
            {
                right--;
            }
            else
            {
                ans.push_back({nums[i], nums[left], nums[right]});

                left++;
                right--;

                while (left < right && nums[left] == nums[left - 1])
                {
                    left++; // skip duplicate second value
                }

                while (left < right && nums[right] == nums[right + 1])
                {
                    right--; // skip duplicate third value
                }
            }
        }
    }

    return ans;
}

int main(int argc, char *argv[])
{
    vector<int> test{1, 2, 0, 1, 0, 0, 0, 0};
    int value{3};

    vector<vector<int>> result = threeSum(test);

    for (const vector<int> &i : result)
    {

        for (const int &j : i)
        {
            cout << j << ", ";
        }

        cout << endl;
    }
}
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

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
    vector<int> test{1, 0, 1, 1};
    cout << containsNearbyDuplicate(test, 0);
}
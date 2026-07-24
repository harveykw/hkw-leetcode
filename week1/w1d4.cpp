#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

/*
Sliding Window and prefix sum



Array {2, 3, 5, 1, 5}
Prefix Array {2, 5, 10, 11, 16}

Range: 1-> 3 (literally take position 3 minus position 1)

*/

class NumArray
{

    int *numsData;
    vector<int> prefix{};

    int sum{0};

public:
    NumArray(vector<int> &nums)
    {
        numsData = nums.data();
        // Construct and store prefix array

        for (int i{0}; i < nums.size(); ++i)
        {
            if (i == 0)
            {
                prefix.push_back(nums[i]);
                // cout << nums[i] << endl;
                continue;
            }

            // cout << (nums[i]) << " plus " << nums[i - 1] << " is " << (nums[i] + prefix[i - 1]) << endl;
            prefix.push_back((nums[i] + prefix[i - 1]));
        }
    }

    int sumRange(int left, int right)
    {

        if (left == 0)
        {
            return prefix[right];
        }
        if (left == right)
        {
            return (numsData[left]);
        }
        return (prefix[right] - prefix[left - 1]);
    }
};

/*


3,0,1
5,6,3

3,3,4
8,14,18

To build a 2D prefix sum array, create a new
 table (pref) to handle boundary conditions easily.
 Iterate through the original matrix (arr) using nested loops, calculating pref[i][j] as the
 current element plus the sums of the top and left cells, minus the top-left diagonal (to remove double-counting),

*/

class NumMatrix
{
    vector<vector<int>> prefix;

public:
    NumMatrix(vector<vector<int>> &matrix)
    {
        prefix = matrix;

        // Populate prefix
        for (int i{0}; i < prefix.size(); ++i)
        {

            // Starting position
            for (int j{0}; j < prefix[0].size(); ++j)
            {
                if (i == 0 && j == 0)
                    continue;
            }

            // Adding columns
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
    }
};

int main(int argc, char *argv[])
{
    // -2, -2, 1
    vector<int> test{-2, 0, 3, -5, 2, -1};
    NumArray *obj = new NumArray(test);
    int sum = obj->sumRange(0, 2); // 1
    cout << sum << endl;
    sum = obj->sumRange(2, 5); //-1
    cout << sum << endl;
    sum = obj->sumRange(0, 5); //-3
    cout << sum << endl;
}

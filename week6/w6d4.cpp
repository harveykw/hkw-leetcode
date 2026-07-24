#include <iostream>
#include <vector>

using std::vector, std::cout;

class Solution
{
    bool found{false};

public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int low = 0;
        int high = nums.size() - 1;
        vector<int> range{-1, -1};

        while (low <= high)
        {
            int mid = low + ((high - low) / 2);

            // base - find the start of the target range
            if (nums[mid] == target && ((mid == 0) || (nums[mid - 1] != target)))
            {
                found = true;
                range.at(0) = mid;
                break;
            }

            bool leqTarget = (nums[mid] >= target);
            high = (leqTarget) ? mid - 1 : high;
            low = (!leqTarget) ? mid + 1 : low;
        }

        if (found)
        {
            low = range.at(0);
            high = nums.size() - 1;
            while (low <= high)
            {
                int mid = low + ((high - low) / 2);

                // base - find the end of the target range
                if (nums[mid] == target && ((mid == nums.size() - 1) || (nums[mid + 1] != target)))
                {
                    range.at(1) = mid;
                    break;
                }

                bool gtTarget = (nums[mid] > target);
                high = (gtTarget) ? mid - 1 : high;
                low = (!gtTarget) ? mid + 1 : low;
            }
        }

        return range;
    }
};

int main(int argc, char *argv[])
{
    vector<int> test{1, 2, 2};
    Solution sol{};
    vector<int> result = sol.searchRange(test, 2);
    cout << result.at(0) << ", " << result.at(1);
}
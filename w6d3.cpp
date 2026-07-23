#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution
{

public:
    int search(vector<int> &nums, int target)
    {
        int low = 0;
        int high = nums.size() - 1;
        bool rotated{false};
        if (nums[low] > nums[high])
        {
            rotated = true;
        }

        while (low <= high)
        {
            int mid = low + ((high - low) / 2);
            if (nums[mid] == target)
                return mid;

            if (rotated)
            {
                // Check to see which half is properly ordered
                int sortedLeft, sortedRight, unsortedLeft, unsortedRight; // Bounds of the sorted array

                bool isLeftSorted{nums[low] < nums[mid]};

                sortedLeft = (isLeftSorted) ? low : mid + 1;
                sortedRight = (isLeftSorted) ? mid - 1 : high;

                unsortedLeft = (isLeftSorted) ? mid + 1 : low;
                unsortedRight = (isLeftSorted) ? high : mid - 1;

                bool targetInSortedHalf{nums[sortedLeft] <= target && target <= nums[sortedRight]};
                low = (targetInSortedHalf) ? sortedLeft : unsortedLeft;
                high = (targetInSortedHalf) ? sortedRight : unsortedRight;
                if (targetInSortedHalf)
                    rotated = false;
            }
            else
            {
                if (target < nums[mid])
                {
                    high = mid - 1; // left
                }
                else
                {
                    low = mid + 1; // right
                }
            }
        }
        return -1;
    }
};

int main(int argc, char *argv[])
{
    vector<int> test{2, 1};
    Solution sol{};

    std::cout << sol.search(test, 1);
}
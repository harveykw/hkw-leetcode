#include <iostream>
#include <vector>

using std::vector, std::cout, std::string;

/*
Do do recursion:

I need a base case to default to/exit the recursion. This usually
happens when the search space or whatnot is exhausted


*/

int search(vector<int> &nums, int low, int high, int target)
{

    // Cases at the edges
    if (target < nums[low])
        return low;
    if (target > nums[high])
        return high + 1;

    // mid calculation + matching
    int mid = low + ((high - low) / 2);
    if (target == nums[mid])
        return mid;

    // The case where low and hign are next to each other
    if (low == mid)
        return high;

    if (target < nums[mid])
    {
        return search(nums, low, mid, target);
    }
    else
    {

        return search(nums, mid, high, target);
    }
}

int searchInsert(vector<int> &nums, int target)
{
    int low = 0;
    int high = nums.size() - 1;
    return search(nums, low, high, target);
}

int main(int argc, char *argv[])
{
    vector<int> nums{1, 3, 5, 6};
    cout << searchInsert(nums, 2);
}
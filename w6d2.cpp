#include <iostream>
#include <vector>
#include <utility>

using std::vector, std::pair;

class Solution
{
private:
    enum class Larger
    {
        Left,
        Right,
        None
    };

    pair<bool, Larger> isPeak(vector<int> &nums, int midIndex)
    {

        if (nums.size() == 1)
        {
            return {true, Larger::None};
        }

        int currentNumber = nums[midIndex];
        // From this point on, all nums array are guarenteed to be size 2 or more
        if (midIndex == 0)
        {
            // Check right
            return (currentNumber > nums[midIndex + 1]) ? std::make_pair(true, Larger::None) : std::make_pair(false, Larger::Right);
        }

        if (midIndex == nums.size() - 1)
        {
            // Check left
            return (currentNumber > nums[midIndex - 1]) ? std::make_pair(true, Larger::None) : std::make_pair(false, Larger::Left);
        }

        // check middle
        int left = nums[midIndex - 1];
        int right = nums[midIndex + 1];
        Larger biggerNumber = (left > right) ? Larger::Left : Larger::Right;

        if (currentNumber > left && currentNumber > right)
        {
            return {true, biggerNumber};
        }

        return {false, biggerNumber};
    }

    int recursiveFindPeak(vector<int> &nums, int left, int right)
    {
        int midIndex = left + ((right - left) / 2);
        auto [peak, bigger] = isPeak(nums, midIndex);
        // Default case where mid is peak
        if (peak)
            return midIndex;

        // If not peak, check to see which side is larger
        switch (bigger)
        {
        case Larger::Left:
            return recursiveFindPeak(nums, left, midIndex);
            break;

        case Larger::Right:
            return recursiveFindPeak(nums, midIndex + 1, right);
            break;

        default:
            throw std::runtime_error{"No larger neighbors despite not being the peak"};
        }
    }

public:
    int findPeakElement(vector<int> &nums)
    {
        return recursiveFindPeak(nums, 0, nums.size() - 1);
    }
};

int main(int argc, char *argv[])
{

    vector<int> test{1};
    Solution sol{};

    std::cout << sol.findPeakElement(test);
}
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using std::vector, std::string, std::pair;

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {

        vector<string> returnVector{};
        if (nums.empty())
            return returnVector;

        vector<pair<int, int>> rangeVector{};

        for (const int &currentNumber : nums)
        {
            if (rangeVector.empty())
            {
                rangeVector.push_back({currentNumber, currentNumber});
                continue;
            }

            // Increase upper bound
            if (currentNumber == rangeVector.back().second + 1)
            {
                rangeVector.back().second = currentNumber;
                continue;
            }

            // Create new range
            rangeVector.push_back({currentNumber, currentNumber});
        }

        for (const pair<int, int> &currentPair : rangeVector)
        {
            if (currentPair.first == currentPair.second)
            {
                returnVector.push_back(std::to_string(currentPair.first));
                continue;
            }

            returnVector.push_back(std::to_string(currentPair.first) + "->" + std::to_string(currentPair.second));
        }

        return returnVector;
    }
};

int main(int argc, char *argv[])
{
}
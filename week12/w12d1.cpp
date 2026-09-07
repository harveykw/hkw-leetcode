#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

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

    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> returnVector{};
        if (intervals.empty())
            return returnVector;

        // Sort by first element, then tie break with latter elements as default vector sorting behavior
        std::sort(intervals.begin(), intervals.end());

        for (const auto &interval : intervals)
        {
            if (returnVector.empty())
            {
                returnVector.push_back(interval);
                continue;
            }

            // case one - fully contained
            if (interval.at(0) >= returnVector.back().at(0) && interval.at(1) <= returnVector.back().at(1))
                continue;

            // case two - partial containment
            if (interval.at(0) >= returnVector.back().at(0) && interval.at(0) <= returnVector.back().at(1))
            {
                returnVector.back().at(1) = interval.at(1);
                continue;
            }

            // case three - disjoint interval
            returnVector.push_back(interval);
        }

        return returnVector;
    }
};

int main(int argc, char *argv[])
{
}
#include <iostream>
#include <vector>

using std::vector;

class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        vector<vector<int>> returnVector{};

        int newStart{newInterval.at(0)};
        int newEnd{newInterval.at(1)};

        if (intervals.empty())
        {
            returnVector.push_back({newStart, newEnd});
            return returnVector;
        }

        bool inserted{false};

        int i{0};

        // Get Start

        for (i; i < intervals.size(); ++i)
        {
            const auto currentInterval{intervals.at(i)};

            int currentStart{currentInterval.at(0)};
            int currentEnd{currentInterval.at(1)};

            if (newStart > currentEnd)
            {
                returnVector.push_back(currentInterval);
                continue;
            }

            newStart = (newStart < currentStart) ? newStart : currentStart;

            newEnd = (newEnd >= currentStart && newEnd < currentEnd) ? currentEnd : newEnd;

            if (currentStart > newEnd)
            {

                if (!inserted)
                {
                    returnVector.push_back({newStart, newEnd});
                    inserted = true;
                }

                returnVector.push_back(currentInterval);
                continue;
            }
        }

        if (!inserted)
            returnVector.push_back({newStart, newEnd});

        return returnVector;
    }
};

int main(int argc, char *argv[])
{
}
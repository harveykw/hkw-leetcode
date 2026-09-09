#include <iostream>
#include <vector>
#include <algorithm>

using std::vector, std::pair;

class Solution
{
public:
    // Note this solution is not the most efficient as I can just store a single overlap instead of a vector since this problem is only asking for the miniumum number of arrows
    // However if it requires us to know where those arrows should be, this solution should be optimal.

    int findMinArrowShots(vector<vector<int>> &points)
    {
        if (points.empty())
            return 0;
        vector<vector<int>> overlaps{};

        std::sort(points.begin(), points.end());

        for (const auto &interval : points)
        {
            if (overlaps.empty())
            {
                overlaps.push_back(interval);
                continue;
            }

            // Calculate an overlap
            int overlapStart{overlaps.back().at(0)};
            int overlapEnd{overlaps.back().at(1)};

            int curStart{interval.at(0)};
            int curEnd{interval.at(1)};

            // Overlap detected - Only works because intervals are in sorted order
            if (curStart >= overlapStart && curStart <= overlapEnd)
            {

                // Determine new overlap and replace
                int newStart = std::max(curStart, overlapStart);
                int newEnd = std::min(curEnd, overlapEnd);

                overlaps.back() = {newStart, newEnd};
                continue;
            }
            overlaps.push_back(interval);
        }
        return overlaps.size();
    }
};

int main(int argc, char *argv[])
{
}
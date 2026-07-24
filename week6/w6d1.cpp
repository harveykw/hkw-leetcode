#include <iostream>
#include <vector>

using std::vector, std::cout;

class Solution
{

private:
    bool binarySearch(const vector<int> &array, int target, int start, int end)
    {
        if (target == array.at(start) || target == array.at(end))
        {
            return true;
        }

        int midIndex{start + ((end - start + 1) / 2)};
        int midValue{array.at(midIndex)};

        if (target == midValue)
            return true;

        // If end and start are next to each other
        if ((end - start) < 2)
            return false;

        if (target < midValue)
        {
            // Check left subhalf
            return binarySearch(array, target, start, midIndex);
        }
        else
        {
            // Check right subhalf
            return binarySearch(array, target, midIndex, end);
        }
    }

public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        // First Step is to find the row that would contain the target number
        for (const vector<int> &row : matrix)
        {

            // We check the last element of each row to check the back
            int currentLast{row.back()};
            if (target == currentLast)
                return true;
            if (target < currentLast)
            {
                // found the row
                return binarySearch(row, target, 0, row.size() - 1);
            }
        }

        return false;
    }
};

int main(int argc, char *argv[])
{

    vector<vector<int>> testInput{{1, 3}};

    Solution testSol{};
    cout << testSol.searchMatrix(testInput, 1);
}
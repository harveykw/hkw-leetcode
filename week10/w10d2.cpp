#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::vector, std::unordered_map, std::unordered_set;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        // First lets build the dependency map: Prereq -> courses that require them
        unordered_map<int, vector<int>> depMap{};

        // Maintain vector that holds counts of prereqs for each course

        vector<int> depCount(numCourses, 0);

        for (const auto &entry : prerequisites)
        {
            int course{entry.front()};
            int prereq{entry.back()};

            // Increase dep count
            depCount.at(course)++;

            // Using default init behaviour of map
            depMap[prereq].push_back(course);
        }

        // Generate a set of courses with no prereqs from depCounts
        unordered_set<int> freeCourses{};
        for (int i{0}; i < numCourses; i++)
        {
            int count{depCount.at(i)};

            if (count == 0)
            {
                freeCourses.insert(i);
            }
        }

        vector<int> returnVector{};

        while (!freeCourses.empty())
        {
            // Deref begin iter to get arbitrary element
            int element = *freeCourses.begin();
            returnVector.push_back(element);
            freeCourses.erase(element);

            // Decrement dep counts with this element
            if (depMap.find(element) != depMap.end())
            {
                for (const auto &dependent : depMap[element])
                {
                    int count = --depCount[dependent];
                    if (count == 0)
                        freeCourses.insert(dependent);
                }
            }
        }

        if (returnVector.size() != numCourses)
            return {};

        return returnVector;
    }
};

int main(int argc, char *argv[])
{
    vector<vector<int>> test{{1, 0}, {1, 2}, {0, 1}};

    Solution sol{};
    auto returnVec = sol.findOrder(3, test);

    for (const auto &e : returnVec)
    {
        std::cout << e << ", ";
    }
}
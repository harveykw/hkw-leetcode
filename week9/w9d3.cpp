#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {

        unordered_map<int, vector<int>> dependencyBank{};

        for (const auto &dependency : prerequisites)
        { // All prereq pairs are guaranteed to be unique

            // Get rid of self cycles

            if (dependency.at(0) == dependency.at(1))
                return false;

            // Check dependency to make sure it is not a cycle
            unordered_set<int> visited{};
            queue<int> depsToCheck{};

            // Preload head of chain
            visited.insert(dependency.at(0));
            depsToCheck.push(dependency.at(1));

            // While there is a valid dependency to process
            while (!depsToCheck.empty())
            {

                // Get the current dependency
                int currentDep = depsToCheck.front();
                depsToCheck.pop();

                // If the current dependency does not have a dependency, continue checking any other queued dependencies
                if (dependencyBank.find(currentDep) == dependencyBank.end())
                    continue;

                // If the current dependency has dependencies, we loop through all subdependencies
                for (int subDependency : dependencyBank[currentDep])
                {

                    // If a subdependency leads back to the course being added, false. Cycle detected
                    if (subDependency == dependency.at(0))
                        return false;

                    // Add the subdependency to the checked set. If it has not already been checked and has
                    // dependencies of its own, add the subdependency to be investigated
                    if (visited.insert(subDependency).second &&
                        dependencyBank.find(subDependency) != dependencyBank.end())
                    {
                        depsToCheck.push(subDependency);
                    }
                }
            }

            // Use default behavior on purpose. This inits if not found
            dependencyBank[dependency.at(0)].push_back(dependency.at(1));
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
}

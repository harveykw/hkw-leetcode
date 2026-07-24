#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

bool canConstruct(string ransomNote, string magazine)
{
    unordered_map<char, int> wordBank{};

    for (const char c : magazine)
    {

        // We can do this because in the absence of an entry, c++ inserts it with a default value. It is a 0 for ints, floats, and doubles
        wordBank[c]++;
        // if (wordBank.find(c) == wordBank.end())
        // {
        //     wordBank[c] = 1;
        // }
        // else
        // {
        //     wordBank[c]++;
        // }
    }

    for (const char c : ransomNote)
    {
        if (wordBank.find(c) == wordBank.end())
            return false;

        wordBank[c]--;
        if (wordBank[c] < 0)
            return false;
    }

    return true;
}

int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{

    if (gas.empty() || cost.empty())
    {
        return -1;
    }

    vector<int>::iterator it1 = gas.begin();
    vector<int>::iterator it2 = cost.begin();

    vector<int>::iterator current = it1;

    int fuelTank{0};
    bool looped{false};
    int steps{0};

    while (steps < gas.size())
    {

        // Refuel
        fuelTank += *it1;
        ++it1;
        // Spend Fuel to get to next
        fuelTank -= *it2;
        ++it2;

        ++steps;

        //  We need to update i to reset to 0 to ensure a full loop on failure
        if (fuelTank < 0)
        {
            if (looped)
                return -1;
            current = it1;
            fuelTank = 0;
            steps = 0;
        }

        // We need to handle looping past the end
        if (it1 == gas.end())
        {
            it1 = gas.begin();
            it2 = cost.begin();
            looped = true;
        }
    }

    return distance(gas.begin(), current);
}

int main(int argc, char *argv[])
{

    string testRansom{"action"};
    string testMagazine("application");

    cout << canConstruct(testRansom, testMagazine);

    // vector<int> testGas{5, 1, 2, 3, 4};
    // vector<int> testCost{4, 4, 1, 5, 1};
    // cout << canCompleteCircuit(testGas, testCost);
}